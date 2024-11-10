#pragma once

#include "gpio.hpp"
#include <deque>
#include <memory>

namespace HAL::UART{

    enum USART_ID{
        USART_1 = 1,
        USART_2,
        USART_3,
        USART_4
    };
    enum CTRL_REG_1{
        ENABLE_USART        = USART_CR1_UE,
        ENABLE_RX           = USART_CR1_RE,
        ENABLE_TX           = USART_CR1_TE,
        RX_NOT_EMPTY_ISR    = USART_CR1_RXNEIE_RXFNEIE,
        TX_COMPLETE_ISR     = USART_CR1_TCIE,
        TX_EMPTY_ISR        = USART_CR1_TXEIE_TXFNFIE  
    };

    class USART {
        public:
            USART() = default;
            
            USART(
                USART_ID instance, 
                std::unique_ptr<HAL::GPIO::AF::GPIO_AF> _rx, 
                std::unique_ptr<HAL::GPIO::AF::GPIO_AF> _tx
            );

            // Configuration
            void configure_baud_rate(uint32_t sysclock_mhz, uint32_t baud);
            void enable_rs485_driver(std::unique_ptr<HAL::GPIO::AF::GPIO_AF> rtsPin);
            void set_cr1_flag(CTRL_REG_1 flg);
            USART_TypeDef* usartInst = nullptr;
            std::deque<uint8_t> rxBuff, txBuff;
        protected:
            std::unique_ptr<HAL::GPIO::AF::GPIO_AF> rx, tx, rts;
            USART_TypeDef *get_usart_instance(USART_ID target);
    };
}
