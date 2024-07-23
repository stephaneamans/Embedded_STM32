# Makefile for nRF9160 bare metal programming                 PVH, January 2023

# Arm GNU toolchain can be found here (look for gcc-arm-none-eabi)
# https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
# nrfx is available at https://github.com/NordicSemiconductor/nrfx
# and the SDK at https://github.com/nrfconnect/sdk-nrfxlib
# CMSIS can be found at https://github.com/ARM-software/CMSIS_5


# Specify project name, build directory and linker script
TARGET = test
BUILDDIR = ./build
LDSCRIPT = LinkerScript.ld

# Paths to toolchain and SDK
TOOLSPATH = /opt/gcc-arm-none-eabi-9-2020-q2-update

# Shortcuts for various tools
MERGEHEX = /opt/nrf-command-line-tools/bin/mergehex
# Shortcuts for various tools
CC  = arm-none-eabi-gcc
AS  = arm-none-eabi-as
LD  = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZETOOL = arm-none-eabi-size



# List of source files for the application
SOURCES = \
    app/startup_stm32.s \
    app/clock.c \
    app/dma.c \
    app/driver_initialization.c \
    app/gpio.c \
    app/nvic.c \
	app/spi.c \
	app/systick.c \
	app/timer.c \
	app/usart.c
    
# List of include directories
INCLUDEDIRS = app









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
OBJECTS = $(notdir $(subst .c,.o,$(SOURCES)))

# Finally, add build directory prefix
OBJECTS := $(addprefix $(BUILDDIR)/objects/bsw/,$(OBJECTS))


SOURCES := $(addprefix $(SOURCES_FOLDER),$(SOURCES))
#SOURCES_PATH := $(foreach path, $(SOURCES), $(subst $(lastword $(subst /, ,$(firstword $(path)))),,$(firstword $(path))))

#OK fonctionne
#SOURCES_PATH := $(foreach path, $(SOURCES), $(addprefix $(SOURCES_FOLDER), $(subst $(lastword $(subst /, ,$(firstword $(path)))),,$(firstword $(path)))))

#le meme mais sans source folder fait plus haut, ok fonctionne
#SOURCES_PATH := $(foreach path, $(SOURCES), $(subst $(lastword $(subst /, ,$(firstword $(path)))),,$(firstword $(path)))))

#le meme mais avec retrait des espaces.
SOURCES_PATH += $(strip $(foreach path, $(SOURCES), $(subst $(lastword $(subst /, ,$(firstword $(path)))),,$(firstword $(path)))))




# Add -I prefix to INCLUDEDIRS and insert them into CFLAGS, CPPFLAGS and AFLAGS
CFLAGS := $(CFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 
CPPFLAGS := $(CPPFLAGS) $(addprefix -I,$(INCLUDEDIRS))
AFLAGS := $(AFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 







































# Flags for the assembler
AFLAGS = ${FLAGS}

# Construct list of object files by appending the suffix .o to all source files
OBJECTS := $(addsuffix .o,$(SOURCES))

# Finally, add build directory prefix
OBJECTS := $(addprefix $(BUILDDIR)/,$(OBJECTS))

# Add -I prefix to INCLUDEDIRS and insert them into CFLAGS, CPPFLAGS and AFLAGS
CFLAGS := $(CFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 
AFLAGS := $(AFLAGS) $(addprefix -I,$(INCLUDEDIRS)) 


all: $(BUILDDIR)/$(TARGET).hex

$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET)_app.axf
	@echo "[MERGEHEX] $^ -> $@"
	@$(MERGEHEX) -m $^ -o $@
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET).bin"
	@objcopy -I ihex -O binary $@ $(BUILDDIR)/$(TARGET).bin
		
$(BUILDDIR)/$(TARGET)_app.axf: $(OBJECTS) 
	@echo "[LD] Linking app image $@"
	@$(LD) $(LDFLAGS) -DNRF_TRUSTZONE_NONSECURE -o $@ $(OBJECTS) $(LIBS)
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.hex"
	@objcopy -O ihex $@ $(BUILDDIR)/$(TARGET)_app.hex
	@echo "[OBJCOPY] $@ -> $(BUILDDIR)/$(TARGET)_app.bin"
	@objcopy -I ihex -O binary $(BUILDDIR)/$(TARGET)_app.hex $(BUILDDIR)/$(TARGET)_app.bin
	@$(SIZETOOL) $@

# Recipe for building C objects in the application
$(BUILDDIR)/app/%.c.o: app/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(@D)
	@$(CC) $(NSFLAGS) $(CFLAGS) -c $< -o $@

# Recipe for assembling objects in the application
$(BUILDDIR)/app/%.s.o: app/%.s
	@echo "[AS] $< -> $@"
	@mkdir -p $(@D)
	@$(AS) $(NSFLAGS) $(AFLAGS) -c $< -o $@


.PHONY: clean

# Remove all build files
clean:
	@echo "Removing $(BUILDDIR)"
	@rm -dfr $(BUILDDIR)
