SRC = configuration/

OBJS += \
$(BUILD_OBJ_DIR)bsp_configuration.o

C_INCLUDE += \
-I$(ROOT_DIR)/configuration/include \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include/reg_base \
-I$(ROOT_DIR)/drivers/api

-include make/makefile_rules.mk
	