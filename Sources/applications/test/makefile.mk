SRC = applications/test/

OBJS += \
$(BUILD_OBJ_DIR)main.o \
$(BUILD_OBJ_DIR)test_usart.o

C_INCLUDE += \
-I$(ROOT_DIR)/applications/test/include \
-I$(ROOT_DIR)/drivers/api \
-I$(ROOT_DIR)/drivers/library/include

-include make/makefile_rules.mk
