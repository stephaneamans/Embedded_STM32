# Define root directory:
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Define build directories:
override BUILD_DIR := $(or $(BUILD_DIR), $(ROOT_DIR)build/)
override BUILD_OBJ_DIR = $(BUILD_DIR)objects/

#Define tollchain:
TOOL_CHAIN = arm-none-eabi

# All of the sources participating in the build are defined here
-include make/makefile_rules.mk
-include target/stm32f103c8tx/makefile.mk
-include applications/test/makefile.mk
-include drivers/makefile.mk
-include drivers/stm32f1_lld/makefile.mk
-include drivers/stm32f1_lld/cpu/makefile.mk
-include services/makefile.mk
-include configuration/makefile.mk

# All Target
all: test_c.elf

test_c.elf: $(OBJS) $(ROOT_DIR)/target/stm32f103c8tx/LinkerScript.ld
	echo $(OBJS)
	@$(LD) $(LDFLAGS) -o "$(BUILD_DIR)test_c.elf" $(OBJS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	rm -rf $(BUILD_DIR)

post-build:
	-@echo 'Generating binary and Printing size information:'
	$(CP) -O binary "$(BUILD_DIR)test_c.elf" "$(BUILD_DIR)test_c.bin"
	$(SZ) "$(BUILD_DIR)test_c.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
