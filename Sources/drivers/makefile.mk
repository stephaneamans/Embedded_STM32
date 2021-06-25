SRC = drivers/

OBJS += \
$(BUILD_OBJ_DIR)bsp.o \

C_INCLUDE += \
-I$(ROOT_DIR)/drivers/api \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include \
-I$(ROOT_DIR)/drivers/library/include \
-I$(ROOT_DIR)/configuration/include

-include make/makefile_rules.mk 
