#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "main.hpp"
#include "Led.hpp"

void app_main();
extern "C" int main() {
    app_main();
	return 0;
}

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "StayAlive",
  .stack_size = 257,
  .priority = (osPriority_t) osPriorityNormal,
};


void SystemClockInit(){
    SET_BIT(RCC->CR, RCC_CR_HSION); // Enable HSI
    while (!(RCC->CR & RCC_CR_HSIRDY)); // Wa2it for HSI to stabilize

    /* Configure the AHB prescaler (HCLK) to 1 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_0);

    /* Configure the APB1 prescaler (PCLK1) to 1 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, RCC_CFGR_PPRE_0);

    /* Select HSI as the system clock source */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SWS_HSISYS);

    /* Wait for HSI to be used as the system clock */
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSISYS);

    /* Configure the voltage scaling */
    MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_CR1_VOS_0); // Voltage scale 1

    /* Configure flash latency (0 wait states) */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_0);
	SystemCoreClockUpdate();
}

void StayAlive(void *argument){
	Device::Led::RGBLed rgbHandler(
		new HAL::GPIO::OUTPUT::GPIO_OUTPUT(HAL::GPIO::AVAILABLE_PORTS::PORTB, 8), // R
		new HAL::GPIO::OUTPUT::GPIO_OUTPUT(HAL::GPIO::AVAILABLE_PORTS::PORTB, 9), // G
		new HAL::GPIO::OUTPUT::GPIO_OUTPUT(HAL::GPIO::AVAILABLE_PORTS::PORTB, 7)  // B
	);
	while(1){
		// Reset Watchdog
		rgbHandler.set_color(Device::Led::Colors::GREEN);
		osDelay(1000);
	}
}

void app_main() {
	SystemClockInit();
	// Initialize FreeRTOS and threads
	osKernelInitialize();
	defaultTaskHandle = osThreadNew(StayAlive, NULL, &defaultTask_attributes);
	
	osKernelStart();

    /* Loop forever */
	while (1)
	{

	}
}
