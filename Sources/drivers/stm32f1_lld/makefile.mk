SRC = drivers/stm32f1_lld/

OBJS += \
$(BUILD_OBJ_DIR)lld_clock.o \
$(BUILD_OBJ_DIR)lld_dma.o \
$(BUILD_OBJ_DIR)lld_gpio.o \
$(BUILD_OBJ_DIR)lld_nvic.o \
$(BUILD_OBJ_DIR)lld_spi.o \
$(BUILD_OBJ_DIR)lld_usart.o

C_INCLUDE += \
-I$(ROOT_DIR)/configuration/include \
-I$(ROOT_DIR)/drivers/api \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include \
-I$(ROOT_DIR)/drivers/stm32f1_lld/include/regbase \
-I$(ROOT_DIR)/drivers/library/include \


-include make/makefile_rules.mk 
