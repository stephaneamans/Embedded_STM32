CC = $(TOOL_CHAIN)-gcc
LD = $(TOOL_CHAIN)-gcc
AS = $(TOOL_CHAIN)-as
CP = $(TOOL_CHAIN)-objcopy
SZ = $(TOOL_CHAIN)-size

ASFLAGS += \
          -mcpu=cortex-m3 \
          -mthumb
          
CFLAGS += \
          $(ASFLAGS) \
          -Wall \
          -Wextra \
          -O0 \
          -g3 \
          -fmessage-length=0 \
          -ffunction-sections \
          -fdata-sections \
          -c 
  
LDFLAGS = \
          $(ASFLAGS) \
          -T"$(ROOT_DIR)target/stm32f103c8tx/LinkerScript.ld" \
          -Wl,-Map=output.map \
          -Wl,--gc-sections \
          -specs=nano.specs \
          -specs=nosys.specs

$(BUILD_OBJ_DIR)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) $(C_INCLUDE) -o "$@" "$<"
