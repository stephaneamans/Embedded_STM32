SRC = applications/test/

OBJS += \
$(BUILD_OBJ_DIR)main.o \
$(BUILD_OBJ_DIR)test_usart.o \
$(BUILD_OBJ_DIR)test_spi.o \
$(BUILD_OBJ_DIR)test_nrf24l01.o

C_INCLUDE += \
-I$(ROOT_DIR)/applications/test/include \
-I$(ROOT_DIR)/drivers/api \
-I$(ROOT_DIR)/drivers/library/include

-include make/makefile_rules.mk
