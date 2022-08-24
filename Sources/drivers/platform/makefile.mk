SRC = drivers/platform/

OBJS += \
$(BUILD_OBJ_DIR)nrf24l01.o

C_INCLUDE += \
-I$(ROOT_DIR)/configuration/include \
-I$(ROOT_DIR)/drivers/platform/include


-include make/makefile_rules.mk 
