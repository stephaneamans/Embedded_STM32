#################################################
# makefile_global.mk                            #
#                                               #
# This file contains all the global parameters. #
#                                               #
# Created on: Sep 8, 2024                       #
# Author: Stéphane Amans                        #
#################################################


##################################
# Shortcuts to compilation tools #
##################################
CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZETOOL := arm-none-eabi-size


######################
# Folders definition #
######################

# Main sources folder:
SOURCES_FOLDER := $(subst project_side/,,$(ROOT_DIR))

# Main build folder:
BUILD_FOLDER := build/

#Basic software sources and build folders:
BSW := bsw/
BSW_SOURCES_FOLDER := $(subst project_side/,,$(BSW_ROOT_DIR))
BSW_BUILD_FOLDER := ${BUILD_FOLDER}${BSW}
BSW_BUILD_OBJ_FOLDER := ${BSW_BUILD_FOLDER}objects/


#############################
# Different prompts display #
#############################

PRINT_SPACE := " "
PRINT_BUILD := "Process build"
PRINT_DIRECTORY := "directory"
PRINT_BSW_OBJECTS := "basic software obects"
PRINT_ASW_OBJECTS := "application obects"
