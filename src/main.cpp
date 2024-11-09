#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.hpp"
#include "led_control.hpp"

extern "C" int main() {
    app_main();
    return 0;
}

void SystemClockInit(){
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
}

void StayAlive(void *pvParameters){
	reset_all_leds();

	ledGreen.toggle_pin();
	while(1){
		// Reset Watchdog
	}
}

void app_main() {
	SystemClockInit();
	xTaskCreate(StayAlive, "StayAliveWatchdog", 128, NULL, 1, NULL);

    vTaskStartScheduler();
    /* Loop forever */
	while (1)
	{

	}
}


void HardFault_Handler(void)
{	
	__disable_irq();
	reset_all_leds();
	ledRed.toggle_pin();
	while (1){

	}
}
void NMI_Handler(void)
{
	while (1)
	{

	}
}

void Reset_Handler(void){

}