SRC = drivers/

OBJS += \
$(BUILD_OBJ_DIR)driver_initialization.o

C_INCLUDE += \
-I$(ROOT_DIR)/configuration/include \
-I$(ROOT_DIR)/drivers/api \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include

-include make/makefile_rules.mk 
