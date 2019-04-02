################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth/lib/EFR32XG21/GCC/subdir.mk
-include protocol/bluetooth/bt_mesh/src/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/emdrv/nvm3/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG21/Source/GCC/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG21/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: btmeshVendor.axf

# Tool invocations
btmeshVendor.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/efr32mg21a020f1024im32.ld" -Wl,--undefined,bg_application_properties,--undefined,__Vectors,--undefined,__aeabi_uldivmod,--undefined,ceil,--undefined,__nvm3Base -Xlinker -no-enum-size-warning -Xlinker -no-wchar-size-warning -Xlinker --gc-sections -Xlinker -Map="btmeshVendor.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o btmeshVendor.axf -Wl,--start-group "./platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.o" "./client_app.o" "./dcd.o" "./gatt_db.o" "./init_app.o" "./init_board_efr32xg2.o" "./init_mcu_efr32xg2.o" "./main.o" "./pti.o" "./retargetio.o" "./retargetserial.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/udelay.o" "./platform/Device/SiliconLabs/EFR32MG21/Source/system_efr32mg21.o" "./platform/emdrv/nvm3/src/nvm3_default.o" "./platform/emdrv/nvm3/src/nvm3_hal_flash.o" "./platform/emdrv/nvm3/src/nvm3_lock.o" "./platform/emdrv/sleep/src/sleep.o" "./platform/emlib/src/em_assert.o" "./platform/emlib/src/em_burtc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_core.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_crypto.o" "./platform/emlib/src/em_emu.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rmu.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_se.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "./protocol/bluetooth/bt_mesh/src/bg_application_properties.o" "./protocol/bluetooth/bt_mesh/src/mesh_lib.o" "./protocol/bluetooth/bt_mesh/src/mesh_serdeser.o" "/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a" "/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/lib/EFR32XG21/GCC/libbluetooth_mesh.a" "/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/lib/EFR32XG21/GCC/libcoex.a" "/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/lib/EFR32XG21/GCC/binapploader.o" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: btmeshVendor.hex'
	arm-none-eabi-objcopy -O ihex "btmeshVendor.axf" "btmeshVendor.hex"
	@echo ' '

	@echo 'Building bin file: btmeshVendor.bin'
	arm-none-eabi-objcopy -O binary "btmeshVendor.axf" "btmeshVendor.bin"
	@echo ' '

	@echo 'Building s37 file: btmeshVendor.s37'
	arm-none-eabi-objcopy -O srec "btmeshVendor.axf" "btmeshVendor.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "btmeshVendor.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) btmeshVendor.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
