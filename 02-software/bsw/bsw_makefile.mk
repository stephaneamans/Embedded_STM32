#########################################
# bsw_makefile.mk                       #
#                                       #
# This file is intended to create lists #
# used to compile the basic software    #
#                                       #
# Created on: Sep 8, 2024               #
# Author: Stéphane Amans                #
#########################################


#############################################################
# Include basic software configuration makefile (generated) #
#############################################################
include bsw/configuration/generated_makefile_config.mk


###########################################
# Create basic software source files list #
###########################################
BSW_SRC_C_FILES := \
${BSW}${SRC_NVIC} \
${BSW}${SRC_SYSTICK} \
${BSW}${SRC_CLOCK} \
${BSW}${SRC_DMA} \
${BSW}${SRC_GPIO} \
${BSW}${SRC_SPI} \
${BSW}${SRC_USART}


#############################################
# Create basic software include folder list #
#############################################

BSW_INCLUDE_FOLDER := \
-I ${BSW}$(INC_CONFIGURATION) \
-I ${BSW}$(INC_NVIC) \
-I ${BSW}$(INC_SYSTICK) \
-I ${BSW}$(INC_CLOCK) \
-I ${BSW}$(INC_DMA) \
-I ${BSW}$(INC_GPIO) \
-I ${BSW}$(INC_SPI) \
-I ${BSW}$(INC_TIMER) \
-I ${BSW}$(INC_USART) \
-I ${BSW}$(INC_DRIVERS) \
-I ${BSW}$(INC_ERROR) \
-I ${BSW}$(INC_FAULT)


############################################################################
# Assemble automaticaly different BSW lists needed for compilation process #
############################################################################

# Create basic software objects list from source files path.
BSW_OBJ := $(foreach filename, $(addsuffix .o, $(basename $(notdir $(BSW_SRC_C_FILES)))),${BSW_BUILD_OBJ_FOLDER}${filename})

# Create basic software list os source folders from source files paths.
BSW_SRC := $(dir $(BSW_SRC_C_FILES))

# Create basic software objects list from source files path.
BSW_OBJ := $(foreach filename, $(addsuffix .o, $(basename $(notdir $(BSW_SRC_C_FILES)))),${BSW_BUILD_OBJ_FOLDER}${filename})


########################
# Basic software rules #
########################

# Rule for C objects modules
${BSW_BUILD_OBJ_FOLDER}%.o: %.c
	@echo "Process " "$@" "module."
	@$(CC) $(CFLAGS) $(BSW_INCLUDE_FOLDER) -o "$@" "$<"
