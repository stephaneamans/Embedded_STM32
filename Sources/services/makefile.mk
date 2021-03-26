SRC = services/

OBJS += \
$(BUILD_OBJ_DIR)fault.o \

C_INCLUDE += \
-I$(ROOT_DIR)/services/include

-include make/makefile_rules.mk 
