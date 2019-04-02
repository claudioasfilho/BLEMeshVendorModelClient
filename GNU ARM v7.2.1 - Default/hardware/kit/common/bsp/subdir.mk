################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/bsp/bsp_stk.c 

OBJS += \
./hardware/kit/common/bsp/bsp_stk.o 

C_DEPS += \
./hardware/kit/common/bsp/bsp_stk.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/bsp/bsp_stk.o: ../hardware/kit/common/bsp/bsp_stk.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-D__STACK_SIZE=0x1000' '-D__HEAP_SIZE=0x1200' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-DMESH_LIB_NATIVE=1' '-DHAL_CONFIG=1' '-DEFR32MG21A020F1024IM32=1' -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/Device/SiliconLabs/EFR32MG21/Include" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/bt_mesh/inc/soc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/hardware/kit/EFR32MG21_BRD4180A/config" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/sleep/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/hardware/kit/common/bsp" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/bt_mesh/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emlib/src" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/bt_mesh/inc/common" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/CMSIS/Include" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/nvm3/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/hardware/kit/common/halconfig" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/protocol/bluetooth/bt_mesh/src" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/nvm3/src" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/hardware/kit/common/drivers" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/Device/SiliconLabs/EFR32MG21/Source" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/uartdrv/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/sleep/src" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/Device/SiliconLabs/EFR32MG21/Source/GCC" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor/platform/halconfig/inc/hal-config" -I"/Users/clfilho/SimplicityStudio/BLEMesh/btmeshVendor" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/bsp/bsp_stk.d" -MT"hardware/kit/common/bsp/bsp_stk.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


