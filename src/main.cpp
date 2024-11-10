#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "main.hpp"
#include "Led.hpp"

extern "C" int main() {
    app_main();
	return 0;
}

Device::Led::RGBLed rgbHandler;

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "StayAlive",
  .stack_size = 128,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t commThreadHandle;
const osThreadAttr_t commThreadHandle_attributes = {
  .name = "Communication",
  .stack_size = 300,
  .priority = (osPriority_t) osPriorityNormal,
};

void SystemClockInit(){
	/* Todo: Move to HAL lib */
	
	/* HSI conf and activation */
	SET_BIT(RCC->CR, RCC_CR_HSION);
	while (!(READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)));
	
	/* Set AHB prescaler*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, 0x00000000U);
	
	/* Set APB1 prescaler*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, 0x00000000U);

	/* Sysclk activation on the HSI */
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, 0x00000000U);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0x00000000U);
	SystemCoreClockUpdate();
}

void StayAlive(void *argument){
	rgbHandler.set_color(Device::Led::Colors::GREEN);
	while(1){
		// Reset Watchdog
		osDelay(1000);
	}
}

void app_main() {
	SystemClockInit();

	// Initialize FreeRTOS and threads
	osKernelInitialize();
	defaultTaskHandle = osThreadNew(StayAlive, NULL, &defaultTask_attributes);
	commThreadHandle = osThreadNew(communication_task,NULL,&commThreadHandle_attributes);
	
	osKernelStart();

    /* Loop forever */
	while (1)
	{

	}
}

extern "C" void HardFault_Handler(void)
{	
	__disable_irq();
	rgbHandler.set_color(Device::Led::Colors::RED);
	NVIC_SystemReset();
}

extern "C" void NMI_Handler(void)
{
	while (1)
	{

	}
}

extern "C" void WWDG_IRQHandler(void){
	rgbHandler.set_color(Device::Led::Colors::RED);
}

// extern "C" void Reset_Handler(void){
// 	__disable_irq();
// 	rgbHandler.set_color(Device::Led::Colors::RED);
// 	NVIC_SystemReset();
// }
