# Makefile for nRF9160 bare metal programming                 PVH, January 2023

# Arm GNU toolchain can be found here (look for gcc-arm-none-eabi)
# https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
# nrfx is available at https://github.com/NordicSemiconductor/nrfx
# and the SDK at https://github.com/nrfconnect/sdk-nrfxlib
# CMSIS can be found at https://github.com/ARM-software/CMSIS_5


# Specify project name, build directory and linker script
TARGET = test
BUILDDIR = ./build
LDSCRIPT = app.ld
BOOTLDSCRIPT = boot.ld

# Paths to toolchain and SDK
TOOLSPATH = /opt/gcc-arm-none-eabi-9-2020-q2-update
CMSISPATH = /opt/CMSIS_5/CMSIS
NRFXPATH = /opt/nrfx-2.10.0
SDKPATH = /opt/sdk-nrfxlib-2.1.3

# Shortcuts for various tools
CC  = ${TOOLSPATH}/bin/arm-none-eabi-gcc
CPP = ${TOOLSPATH}/bin/arm-none-eabi-g++
AS  = ${TOOLSPATH}/bin/arm-none-eabi-g++
LD  = ${TOOLSPATH}/bin/arm-none-eabi-g++
DB  = ${TOOLSPATH}/bin/arm-none-eabi-gdb
OBJCOPY = ${TOOLSPATH}/bin/arm-none-eabi-objcopy
SIZETOOL = ${TOOLSPATH}/bin/arm-none-eabi-size
MERGEHEX = /opt/nrf-command-line-tools/bin/mergehex
NRFJPROG = /opt/nrf-command-line-tools/bin/nrfjprog

# List of source files for the application
SOURCES = \
    ${NRFXPATH}/mdk/gcc_startup_nrf9160.S \
    ${NRFXPATH}/mdk/system_nrf9160.c \
    app/dyma.c \
    app/delay.c \
    app/nrf_modem_os.c \
    app/nrfx_ipc.c \
    app/main.c \
    
# List of source files for the bootloader
BOOTSOURCES = \
    ${NRFXPATH}/mdk/gcc_startup_nrf9160.S \
    ${NRFXPATH}/mdk/system_nrf9160.c \
    boot/main.c

# List of include directories
INCLUDEDIRS = \
    ${CMSISPATH}/Core/Include \
    ${NRFXPATH} \
    ${NRFXPATH}/templates \
    ${NRFXPATH}/mdk \
    ${NRFXPATH}/hal \
    ${NRFXPATH}/drivers/include \
    ${SDKPATH}/nrf_modem/include

# Directories to search for libraries in the linking process
LDDIRS = \
    ${NRFXPATH}/mdk \
    $(SDKPATH)/nrf_modem/lib/cortex-m33/hard-float \
    
# Libraries for the application
LIBS = -lmodem -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group

# Libraries for the bootloader
BOOTLIBS = -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group

# Additional objects for the linker
LDOBJECTS =

# Common flags for CC, CPP, AS and LD
FLAGS = -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mabi=aapcs
FLAGS += -mfpu=fpv5-sp-d16 -DNRF9160_XXAA
FLAGS += -DCONFIG_GPIO_AS_PINRESET -DFLOAT_ABI_HARD

# Common flags for secure code
SFLAGS = -mcmse

# Common flags for non-secure code
NSFLAGS = -DNRF_TRUSTZONE_NONSECURE

# Flags for the C compiler
CFLAGS = ${FLAGS} -std=c99 -Wall

# Flags for the C++ compiler
CPPFLAGS = ${FLAGS} -std=c++11 -Wall

# Flags for the assembler
AFLAGS = ${FLAGS} -x assembler-with-cpp

# Linker flags
LDFLAGS = ${FLAGS} -T "$(LDSCRIPT)" -Xlinker
LDFLAGS += --gc-sections -Xlinker -Map="$(BUILDDIR)/$(TARGET)_app.map" 
LDFLAGS += --specs=nano.specs

BOOTLDFLAGS = ${FLAGS} -T "$(BOOTLDSCRIPT)" -Xlinker
BOOTLDFLAGS += --gc-sections -Xlinker -Map="$(BUILDDIR)/$(TARGET)_boot.map" 
BOOTLDFLAGS += --specs=nano.specs

# Check whether to optimize or build for debugging
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g3 -gdwarf-2
	CPPFLAGS += -Og -g3 -gdwarf-2
	AFLAGS += -g3 -gdwarf-2
	LDFLAGS += -g3
else
	CFLAGS += -O3
	CPPFLAGS += -O3
endif

# Construct list of object files by appending the suffix .o to all source files
OBJECTS := $(addsuffix .o,$(SOURCES))

# Replace NRFX paths since objects here are going to be build in the build dir.
OBJECTS := $(subst $(NRFXPATH),app/nrfx,$(OBJECTS))
OBJECTS := $(subst $(SDKPATH),app/sdk-nrfxlib,$(OBJECTS))

# Finally, add build directory prefix
OBJECTS := $(addprefix $(BUILDDIR)/,$(OBJECTS))

# And we to the same to the bootloader
BOOTOBJECTS := $(addsuffix .o,$(BOOTSOURCES))
BOOTOBJECTS := $(subst $(NRFXPATH),boot/nrfx,$(BOOTOBJECTS))
BOOTOBJECTS := $(subst $(SDKPATH),boot/sdk-nrfxlib,$(BOOTOBJECTS))
BOOTOBJECTS := $(addprefix $(BUILDDIR)/,$(BOOTOBJECTS))

# Add -I prefix to INCLUDEDIRS and insert them into CFLAGS, CPPFLAGS and AFLAGS
CFLAGS := $(CFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 
CPPFLAGS := $(CPPFLAGS) $(addprefix -I,$(INCLUDEDIRS))
AFLAGS := $(AFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 

# Add -L prefix to LDDIRS and and insert them into LDFLAGS along with LIBS
LDFLAGS := $(addprefix -L,$(LDDIRS)) $(LIBS) $(LDFLAGS)
BOOTLDFLAGS := $(addprefix -L,$(LDDIRS)) $(BOOTLIBS) $(BOOTLDFLAGS)

all: $(BUILDDIR)/$(TARGET).hex

$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET)_boot.axf $(BUILDDIR)/$(TARGET)_app.axf
	@echo "[MERGEHEX] $^ -> $@"
	@$(MERGEHEX) -m $^ -o $@
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET).bin"
	@objcopy -I ihex -O binary $@ $(BUILDDIR)/$(TARGET).bin
	
$(BUILDDIR)/$(TARGET)_boot.axf: $(BOOTOBJECTS)
	@echo "[LD] Linking boot image $@"
	@$(LD) $(BOOTLDFLAGS) -o $@ $(BOOTOBJECTS) $(LIBS)
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_boot.hex"
	@objcopy -O ihex $@ $(BUILDDIR)/$(TARGET)_boot.hex
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_boot.bin"
	@objcopy -I ihex -O binary $(BUILDDIR)/$(TARGET)_boot.hex $(BUILDDIR)/$(TARGET)_boot.bin
	@$(SIZETOOL) $@
	
$(BUILDDIR)/$(TARGET)_app.axf: $(OBJECTS) 
	@echo "[LD] Linking app image $@"
	@$(LD) $(LDFLAGS) -DNRF_TRUSTZONE_NONSECURE -o $@ $(OBJECTS) $(LIBS)
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.hex"
	@objcopy -O ihex $@ $(BUILDDIR)/$(TARGET)_app.hex
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.bin"
	@objcopy -I ihex -O binary $(BUILDDIR)/$(TARGET)_app.hex $(BUILDDIR)/$(TARGET)_app.bin
	@$(SIZETOOL) $@
	
# Recipe for building C objects in the bootloader
$(BUILDDIR)/boot/%.c.o: boot/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	$(CC) $(SFLAGS) $(CFLAGS) -c $< -o $@

# Recipe for building C++ objects in the bootloader
$(BUILDDIR)/boot/%.cpp.o: boot/%.cpp
	@echo "[CPP] $< -> $@"
	@mkdir -p $(@D)
	@$(CPP) $(SFLAGS) $(CPPFLAGS) -c $< -o $@

# Recipe for assembling objects in the bootloader
$(BUILDDIR)/boot/%.S.o: /boot/%.S
	@echo "[AS] $< -> $@"
	@mkdir -p $(@D)
	@$(AS) $(SFLAGS) $(AFLAGS) -c $< -o $@

# Recipe for building C objects in $(NRFXPATH) for the bootloader
$(BUILDDIR)/boot/nrfx/%.c.o: $(NRFXPATH)/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	@$(CC) $(SFLAGS) $(CFLAGS) -c $< -o $@

# Recipe for assembling objects in $(NRFXPATH) for the bootloader
$(BUILDDIR)/boot/nrfx/%.S.o: $(NRFXPATH)/%.S
	@echo "[AS] $< -> $@"
	@mkdir -p $(@D)
	@$(AS) $(SFLAGS) $(AFLAGS) -c $< -o $@

# Recipe for building C objects in the application
$(BUILDDIR)/app/%.c.o: app/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	@$(CC) $(NSFLAGS) $(CFLAGS) -c $< -o $@
	
# Recipe for building C++ objects in the application
$(BUILDDIR)/app/%.cpp.o: app/%.cpp
	@echo "[CPP] $< -> $@"
	@mkdir -p $(@D)
	@$(CPP) $(NSFLAGS) $(CPPFLAGS) -c $< -o $@

# Recipe for assembling objects in the application
$(BUILDDIR)/app/%.S.o: app/%.S
	@echo "[AS] $< -> $@"
	@mkdir -p $(@D)
	@$(AS) $(NSFLAGS) $(AFLAGS) -c $< -o $@

# Recipe for building C objects in $(NRFXPATH) for the application
$(BUILDDIR)/app/nrfx/%.c.o: $(NRFXPATH)/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	@$(CC) $(NSFLAGS) $(CFLAGS) -c $< -o $@

# Recipe for assembling objects in $(NRFXPATH) for the application
$(BUILDDIR)/app/nrfx/%.S.o: $(NRFXPATH)/%.S
	@echo "[AS] $< -> $@"
	@mkdir -p $(@D)
	@$(AS) $(NSFLAGS) $(AFLAGS) -c $< -o $@

.PHONY: clean flash erase debug

# Remove all build files
clean:
	@echo "Removing $(BUILDDIR)"
	@rm -dfr $(BUILDDIR)
	
# Flash the program
flash: $(BUILDDIR)/$(TARGET).hex
	@echo Flashing $(BUILDDIR)/$(TARGET).hex
	@$(NRFJPROG) -f nrf91 --program $(BUILDDIR)/$(TARGET).hex --sectorerase \
	--verify --reset

# Erase all flash
erase:
	@echo Erasing all flash
	@nrfjprog -f nrf91 --eraseall

# Shortcut for debugging
debug: $(BUILDDIR)/$(TARGET).hex
	@echo "Run /opt/SEGGER/JLink/JLinkGDBServerCLExe -device nrf9160_xxaa -if swd -port 2331"
	@$(DB) -x gdb_cmds.txt
