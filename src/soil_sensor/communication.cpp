#include <main.h>
#include <gpio_base.h>

void config_usart(){
    // USART3 - RTS PD12 AF7 | TX PD8 AF7 | RX PD9 AF7 | CTS PB13 AF7
    // GPIO Config
    HAL::GPIO::AF::GPIO_AF  usartTx(HAL::GPIO::AVAILABLE_PORTS::PORTD, 8), 
                            usartRx(HAL::GPIO::AVAILABLE_PORTS::PORTD, 9),
                            usartRts(HAL::GPIO::AVAILABLE_PORTS::PORTD, 12),
                            usartCts(HAL::GPIO::AVAILABLE_PORTS::PORTB, 13);

    usartTx.set_alternate_function(HAL::GPIO::AF::AF7);
    usartRx.set_alternate_function(HAL::GPIO::AF::AF7);
    usartRts.set_alternate_function(HAL::GPIO::AF::AF7);
    usartCts.set_alternate_function(HAL::GPIO::AF::AF7);

    // // DMA config Stream 1 channel 4
    // DMA1_Stream4->NDTR 	= DEBUG_RX_BUFFER_SIZE;
    // DMA1_Stream4->PAR 	= (uint32_t)&(USART3->DR);
    // DMA1_Stream4->M0AR 	= (uint32_t)&rxBuffer;
    // DMA1_Stream4->CR 	=  (0b100 << DMA_SxCR_CHSEL_Pos) |
    //                     DMA_SxCR_MINC 				 |
    //                     DMA_SxCR_DIR_0			     |
    //                     DMA_SxCR_TCIE;
    // // USART Config
    // RCC->APB1ENR 	|= (1 << RCC_APB1ENR_USART3EN_Pos);  		// Enable clock USART3
    // USART3->CR3  	|= (1 << USART_CR3_CTSE_Pos)			 |	// Enable CTS
    //                 (1 << USART_CR3_RTSE_Pos);		    	// Enable RTS
    // // Brr = Mantissa + Fraction / Clock (16)
    // uint16_t uartdiv = 1600000 / 115200;
    // USART3->BRR  |= (
    //     (( uartdiv / 16 ) << USART_BRR_DIV_Mantissa_Pos ) | ((uartdiv % 16 ) << USART_BRR_DIV_Fraction_Pos )
    //                 );
    // USART3->CR1  	 |= USART_CR1_UE			 	 |	// Enable USART
    //                     USART_CR1_TE			 	 |	// Enable Tx
    //                     USART_CR1_RE;			    	// Enable Rx
    // DMA1_Stream4->CR |= DMA_SxCR_EN;
    NVIC_EnableIRQ(USART3_4_IRQn);
    NVIC_SetPriority(USART3_4_IRQn, 3);
}