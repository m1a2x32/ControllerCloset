#pragma once

#include <gpio_base.h>

using namespace HAL::GPIO::AF;

namespace HAL::UART{

    enum AVAILABLE_USARTS{
        USART_1 = 1,
        USART_2,
        USART_3,
        USART_4
    };
    
    typedef struct usart
    {
        USART_TypeDef *usartInst;
        GPIO_AF *rx, *tx, *rts = nullptr, *cts = nullptr;
    };
    
    class USART {
        public:
            USART(AVAILABLE_USARTS instance, GPIO_AF *_rx, GPIO_AF *_tx);

            // Configuration
            void configure_baud_rate(uint32_t baud);

            // Flow control
            void enable_flow_control(GPIO_AF *rtsPin, GPIO_AF *ctsPin);
            void disable_flow_control();

            void enable_rs485_driver(GPIO_AF *rtsPin);

            // 
        protected:
            USART_TypeDef *usartInst;
            GPIO_AF *rx, *tx, *rts = nullptr, *cts = nullptr;
            void enable_usart();
            void disable_usart();
    };
    
    bool USART_Check_IsActive_RXNE(USART reg){

    }
}
