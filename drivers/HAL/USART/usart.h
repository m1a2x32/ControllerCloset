#pragma once

#include <gpio_base.h>

namespace HAL::UART{

    enum AVAILABLE_USARTS{
        USART_1 = 1,
        USART_2,
        USART_3,
        USART_4
    };
    
    class USART {
        public:
            USART(AVAILABLE_USARTS instance, HAL::GPIO::AF::GPIO_AF *_rx, HAL::GPIO::AF::GPIO_AF *_tx);

            // Configuration
            void configure_baud_rate(uint32_t baud);
            void enable_rs485_driver(HAL::GPIO::AF::GPIO_AF *rtsPin);
            void enable_usart();
            void disable_usart();
        protected:
            USART_TypeDef *usartInst;
            HAL::GPIO::AF::GPIO_AF *rx, *tx, *rts = nullptr;
            USART_TypeDef *get_usart_instance(AVAILABLE_USARTS target);
    };
}
