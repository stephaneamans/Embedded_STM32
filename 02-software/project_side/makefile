# Makefile for nRF9160 bare metal programming

# Arm GNU toolchain can be found here (look for gcc-arm-none-eabi)
# https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
# nrfx is available at https://github.com/NordicSemiconductor/nrfx
# and the SDK at https://github.com/nrfconnect/sdk-nrfxlib
# CMSIS can be found at https://github.com/ARM-software/CMSIS_5

# Specify project name, build directory and linker script
TARGET = test
BUILDDIR = ./build
LDSCRIPT = LinkerScript.ld

# Shortcuts for various tools
CC  = arm-none-eabi-gcc
AS  = arm-none-eabi-as
LD  = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZETOOL = arm-none-eabi-size

# List of source files for the application
SOURCES = \
    drivers/cpu/nvic/nvic.c \
    drivers/cpu/systick/systick.c \
    drivers/mcu/clock/clock.c \
    drivers/mcu/dma/dma.c \
    drivers/mcu/gpio/gpio.c \
    drivers/mcu/spi/spi.c \
    drivers/mcu/timer/timer.c \
    drivers/usart/usart.c \
    drivers/mcu/driver_initialization.c \
    library/fault/fault.c \

# List of include directories
INCLUDEDIRS = \
    drivers/cpu/nvic \
    drivers/cpu/systick \
    drivers/mcu/clock \
    drivers/mcu/dma \
    drivers/mcu/gpio \
    drivers/mcu/spi \
    drivers/mcu/timer \
    drivers/usart \
    drivers \
    library/error \
    library/fault \
    library/queues \

# Common flags for CC, CPP, AS and LD
FLAGS = -mcpu=cortex-m3 -mthumb

# Flags for the C compiler
CFLAGS = ${FLAGS} -std=c99 -Wall -Wextra -fmessage-length=0 -ffunction-sections -fdata-sections -c 

# Linker flags
LDFLAGS = ${FLAGS} -T "$(LDSCRIPT)"
LDFLAGS += --gc-sections -Xlinker -Map="$(BUILDDIR)/$(TARGET)_app.map" 
LDFLAGS += --specs=nano.specs

# Check whether to optimize or build for debugging
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g3 -gdwarf-2
	AFLAGS += -g3 -gdwarf-2
	LDFLAGS += -g3
else
	CFLAGS += -O3
endif

# Construct list of object files by appending the suffix .o to all source files
OBJECTS := $(addsuffix .o,$(SOURCES))

# Finally, add build directory prefix
OBJECTS := $(addprefix $(BUILDDIR)/,$(OBJECTS))

# Add -I prefix to INCLUDEDIRS and insert them into CFLAGS, CPPFLAGS and AFLAGS
CFLAGS := $(CFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 
CPPFLAGS := $(CPPFLAGS) $(addprefix -I,$(INCLUDEDIRS))
AFLAGS := $(AFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 

# Add -L prefix to LDDIRS and and insert them into LDFLAGS along with LIBS
LDFLAGS := $(addprefix -L,$(LDDIRS)) $(LIBS) $(LDFLAGS)  # !!!! LDDIRS, LIBS removed

all: $(BUILDDIR)/$(TARGET).elf
	
$(BUILDDIR)/$(TARGET).elf: $(OBJECTS) 
	@echo "[LD] Linking app image $@"
	@echo "at link phase = Objects = $(SOURCES)"
	@echo "at link phase = Objects = $(OBJECTS)"
#	@$(LD) $(LDFLAGS) -DNRF_TRUSTZONE_NONSECURE -o $@ $(OBJECTS) $(LIBS)   LIBS removed
#	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.hex"
#	@objcopy -O ihex $@ $(BUILDDIR)/$(TARGET)_app.hex
#	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.bin"
#	@objcopy -I ihex -O binary $(BUILDDIR)/$(TARGET)_app.hex $(BUILDDIR)/$(TARGET)_app.bin
#	@$(SIZETOOL) $@
	
# Recipe for building C objects in the bootloader
#$(BUILDDIR)/boot/%.c.o: boot/%.c
#	@echo "[CC] $< -> $@"
#	@mkdir -p $(@D)
#	$(CC) $(SFLAGS) $(CFLAGS) -c $< -o $@

# Recipe for assembling objects in the bootloader
#$(BUILDDIR)/boot/%.o: /boot/%
#	@echo "[AS] $< -> $@"
#	@mkdir -p $(@D)
#	@$(AS) $(SFLAGS) $(AFLAGS) -c $< -o $@

# Recipe for building C objects in the application
$(BUILDDIR)/app/%.c.o: app/%.c
	@echo "at c phase = Objects = $(SOURCES)"
	@echo "at c phase = Objects = $(OBJECTS)"
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	@$(CC) $(NSFLAGS) $(CFLAGS) -c $< -o $@
	
# Recipe for assembling objects in the application
#$(BUILDDIR)/app/%.o: app/%
#	@echo "at as phase = Objects = $(SOURCES)"
#	@echo "at as phase = Objects = $(OBJECTS)"
#	@echo "[AS] $< -> $@"
#	@mkdir -p $(@D)
#	@$(AS) $(NSFLAGS) $(AFLAGS) -c $< -o $@

.PHONY: clean debug

# Remove all build files
clean:
	@echo "Removing $(BUILDDIR)"
	@rm -dfr $(BUILDDIR)
