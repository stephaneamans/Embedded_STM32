#################################################
# makefile.mk                                   #
#                                               #
# Main make file entry point, this file is used #
# as a central point for this build system.     #
#                                               #
# Created on: Sep 8, 2024                       #
# Author: Stéphane Amans                        #
##################################################


# Create root directory path:
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include make/makefile_flags.mk
include make/makefile_global.mk
include bsw/bsw_makefile.mk

# Create objects list from different lists:
OBJ := ${BSW_OBJ}

# Create VPATH from source files paths:
VPATH = ${BSW_SRC}


TARGET_LIST := \
test.elf \
target2.elf

###################################
# Check for make custom arguments #
###################################

# Check if the first argument is part of the targe list by doing:
#    - $(firstword ${MAKECMDGOALS}) : extract the first word of the MAKECMDGOALS variable from the target list if it exist.
#      This is corresponds to the target name.
#
#    - $(findstring previous_line, ${TARGET_LIST}) : check if the previous result is part of the taraget list.
FIND_TARGET = $(findstring $(firstword ${MAKECMDGOALS}), ${TARGET_LIST})

# If the target is found in the target list, then
ifeq (${FIND_TARGET}, $(findstring ${FIND_TARGET}, ${TARGET_LIST}))

  # Store in the vriable the others arguments, from the second to the last one $(words $(MAKECMDGOALS)).
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  
  # Turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

# If the debug mode is found as argument, then
ifeq (debug, $(findstring ${RUN_ARGS}, debug))

  # Debug mode is switched to active.
  DEBUG = 1

endif


###########
# Targets #
###########

all: test.elf

test.elf : print ${OBJ}

target2.elf : print ${OBJ}

target3.elf : print ${OBJ}

.PHONY: clean print

print:
	@echo $(DEBUG)
	@echo ${PRINT_BUILD} ${PRINT_DIRECTORY}
	@mkdir -p ${BUILD_FOLDER}
	@echo ${PRINT_BUILD} ${PRINT_BSW_OBJECTS} ${PRINT_DIRECTORY}
	@mkdir -p ${BSW_BUILD_OBJ_FOLDER}

clean:
	@rm -rf ${BUILD_FOLDER}
