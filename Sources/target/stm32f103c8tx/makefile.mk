OBJS += \
$(BUILD_OBJ_DIR)startup_stm32.o

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_OBJ_DIR)%.o: target/stm32f103c8tx/%.s
	mkdir -p $(BUILD_OBJ_DIR)
	@$(AS) $(ASFLAGS) -o "$@" "$<"
