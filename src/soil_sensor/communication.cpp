#include <main.h>
#include <usart.h>

HAL::UART::USART soilSensorUsart( HAL::UART::AVAILABLE_USARTS::USART_1, nullptr, nullptr);

void communication_setup(){
    // GPIO Config
    HAL::GPIO::AF::GPIO_AF  usartTx(HAL::GPIO::AVAILABLE_PORTS::PORTD, 8), 
                            usartRx(HAL::GPIO::AVAILABLE_PORTS::PORTD, 9),
                            usartRts(HAL::GPIO::AVAILABLE_PORTS::PORTD, 12);

    usartTx.set_alternate_function(HAL::GPIO::AF::AF7);
    usartRx.set_alternate_function(HAL::GPIO::AF::AF7);
    usartRts.set_alternate_function(HAL::GPIO::AF::AF7);
    
    // USART Config
    soilSensorUsart = HAL::UART::USART(HAL::UART::AVAILABLE_USARTS::USART_1, &usartRx, &usartTx);    
    soilSensorUsart.enable_rs485_driver(&usartRts);

    soilSensorUsart.enable_usart();

    NVIC_EnableIRQ(USART3_4_IRQn);
    NVIC_SetPriority(USART3_4_IRQn, 3);
}

void USART3_4_IRQHandler(){

}