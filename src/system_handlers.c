#include "main.hpp"

void HardFault_Handler(void)
{	
	__disable_irq();
    while (1)
	{

	}
}

void NMI_Handler(void)
{
	while (1)
	{

	}
}

void WWDG_IRQHandler(void)
{
    NVIC_SystemReset();
}
