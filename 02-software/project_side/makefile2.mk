# Makefile for nRF9160 bare metal programming                 PVH, October 2022

# Arm GNU toolchain can be found here (look for gcc-arm-none-eabi)
# https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
# nrfx is available at https://github.com/NordicSemiconductor/nrfx
# CMSIS can be found at https://github.com/ARM-software/CMSIS_5

# Paths to toolchain and SDK
TOOLSPATH = /opt/gcc-arm-none-eabi-9-2020-q2-update
NRFXPATH = /opt/nrfx-2.9.0
CMSISPATH = /opt/CMSIS_5/CMSIS

# Specify project name, object files, headers (DEPS) and linker script
PROJECT = blinky
OBJ = main.o
DEPS =
LDSCRIPT = ${NRFXPATH}/mdk/nrf9160_xxaa.ld
BUILDDIR = ./build

# Startup and system code
ASTART = ${NRFXPATH}/mdk/gcc_startup_nrf9160.S
SYSSRC = ${NRFXPATH}/mdk/system_nrf9160.c

# Common flags for CC, AS and LD
FLAGS = -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mabi=aapcs  
FLAGS += -mfpu=fpv5-sp-d16 -DNRF9160_XXAA
FLAGS += -DCONFIG_GPIO_AS_PINRESET -DFLOAT_ABI_HARD

# Shortcuts for various tools
CC = ${TOOLSPATH}/bin/arm-none-eabi-gcc
AS = ${TOOLSPATH}/bin/arm-none-eabi-gcc
LD = ${TOOLSPATH}/bin/arm-none-eabi-gcc
OBJCOPY = ${TOOLSPATH}/bin/arm-none-eabi-objcopy
SIZETOOL = ${TOOLSPATH}/bin/arm-none-eabi-size

# Compiler flags
CFLAGS = ${FLAGS} -std=c99 -Wall -Werror
CFLAGS += -I"${NRFXPATH}/templates" -I"${NRFXPATH}/mdk"
CFLAGS += -I"${NRFXPATH}" -I"${CMSISPATH}/Core/Include"
CFLAGS += -I"${NRFXPATH}/hal" -I"${NRFXPATH}/drivers/include"

# Assembler flags
AFLAGS = ${FLAGS} -x assembler-with-cpp

# Linker flags
LDFLAGS = ${FLAGS} -T "$(LDSCRIPT)" -Xlinker
LDFLAGS += --gc-sections -Xlinker -Map="$(BUILDDIR)/$(PROJECT).map" 
LDFLAGS += --specs=nano.specs
LDFLAGS += -L"${NRFXPATH}/mdk/"
LIBS = -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group

# Check whether to optimize or build for debugging
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g3 -gdwarf-2
	AFLAGS += -g3 -gdwarf-2
	LDFLAGS += -g3
else
	CFLAGS += -O3
endif

# Substitute the correct path for the object filenames
_OBJ = $(patsubst %,$(BUILDDIR)/%,$(OBJ))

# Define operations
define COMPILE
	@echo "[CC] $< --> $@"
	@$(CC) $(CFLAGS) -c -o $@ $<
endef

define ASSEMBLE
	@echo "[AS] $< --> $@"
	@$(AS) $(AFLAGS) -c -o $@ $<
endef

define OBJECTCOPY
	@echo "[OBJCOPY] $(2)$(3) --> $(2)$(4)"
	@$(OBJCOPY) $(1) $(2)$(3) $(2)$(4)
endef

define CREATEDIR
	@echo "Creating directory $@"
	@mkdir -p $@
endef

# Build the project

$(BUILDDIR)/$(PROJECT).axf: $(_OBJ)  \
    $(BUILDDIR)/cmsis/startup.o $(BUILDDIR)/cmsis/system.o
# Link
	@echo "[LD] $@"
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/$(PROJECT).axf \
	$(BUILDDIR)/cmsis/startup.o \
	$(BUILDDIR)/cmsis/system.o \
	$(addprefix $(BUILDDIR)/, $(OBJ)) $(LIBS)
# Generate hex and bin files
	$(call OBJECTCOPY,-O ihex,$(BUILDDIR)/,"$(PROJECT).axf","$(PROJECT).hex")
	$(call OBJECTCOPY,-O binary,$(BUILDDIR)/,"$(PROJECT).axf","$(PROJECT).bin")
# Run the size tool
	@echo ""
	@$(SIZETOOL) $(BUILDDIR)/"$(PROJECT).axf"
	@echo ""
	
all: $(BUILDDIR)/$(PROJECT).axf

$(BUILDDIR):
	$(call CREATEDIR)

$(BUILDDIR)/cmsis: 	
	$(call CREATEDIR)
	
$(BUILDDIR)/cmsis/startup.o: $(ASTART) | $(BUILDDIR)/cmsis
	$(call ASSEMBLE)
    	
$(BUILDDIR)/cmsis/system.o: $(SYSSRC) | $(BUILDDIR)/cmsis
	$(call COMPILE)

$(BUILDDIR)/%.o: %.c $(DEPS) | $(BUILDDIR)
	$(call COMPILE)
	
# Remove builded stuff
clean:
	rm -dfr $(BUILDDIR)

# Flash the program
flash: $(BUILDDIR)/$(PROJECT).axf
	@echo Flashing $(BUILDDIR)/$(PROJECT).hex
	@nrfjprog -f nrf91 --program $(BUILDDIR)/$(PROJECT).hex --sectorerase \
	--verify --reset

erase:
	@echo Erasing all flash
	@nrfjprog -f nrf91 --eraseall
