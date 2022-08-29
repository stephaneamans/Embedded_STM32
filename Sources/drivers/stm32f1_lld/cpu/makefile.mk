SRC = drivers/stm32f1_lld/cpu/

OBJS += \
$(BUILD_OBJ_DIR)systick.o

C_INCLUDE += \
-I$(ROOT_DIR)/configuration/include \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include

-include make/makefile_rules.mk 
