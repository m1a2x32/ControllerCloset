
#include "usart.hpp"
#include "main.hpp"
#include <string>

using namespace HAL::GPIO;
using namespace HAL::UART;

USART *usart_handle;
void communication_task(void *argument)
{
    auto tx = new AF::GPIO_AF(PORTD, 5, AF::AF0);
    auto rx = new AF::GPIO_AF(PORTD, 6, AF::AF0);
    auto dem = new AF::GPIO_AF(PORTD, 4, AF::AF0);

    usart_handle = new USART(USART_2, rx, tx);
    usart_handle->enable_rs485_driver(dem);
    usart_handle->configure_baud_rate(SystemCoreClock, 9600);
    usart_handle->set_cr1_flag(USART_RX_ENABLE);
    usart_handle->set_cr1_flag(USART_TX_ENABLE);
    usart_handle->set_cr1_flag(TX_COMPLETE_ISR_ENABLE);
    usart_handle->set_cr1_flag(USART_ENABLE);

    NVIC_SetPriority(USART2_IRQn, 3);
    NVIC_EnableIRQ(USART2_IRQn);

    while (1){
        std::string send_data = "hello world!";
        usart_handle->write_data_IT(send_data.c_str(), send_data.length());
        osDelay(2000);
    }
    
}

extern "C" void USART2_IRQHandler()
{
    usart_handle->handle_interrupt();
}
