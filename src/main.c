#include <main.h>

void SystemClockInit(){
	/* HSI conf and activation */
	SET_BIT(RCC->CR, RCC_CR_HSION);
	while (!(READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)));
	
	/* Set AHB prescaler*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, 0x00000000U);
	
	/* Sysclk activation on the HSI */
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, 0x00000000U);
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0x00000000U);

	/* Set APB1 prescaler*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, 0x00000000U);
}

int main(void)
{
	SystemClockInit();
    /* Loop forever */
	for(;;);
}
