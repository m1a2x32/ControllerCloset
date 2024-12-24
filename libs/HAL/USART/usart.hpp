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
        USART_ENABLE                = USART_CR1_UE,
        USART_RX_ENABLE             = USART_CR1_RE,
        USART_TX_ENABLE             = USART_CR1_TE,
        RX_DATA_READY_ISR           = USART_CR1_RXNEIE_RXFNEIE,
        TX_COMPLETE_ISR_ENABLE      = USART_CR1_TCIE,
        TX_BUFFER_EMPTY_ISR_ENABLE  = USART_CR1_TXEIE_TXFNFIE  
    };
    enum CTRL_REG_3{
        ENABLE_RS485                = USART_CR3_DEM,
    };

    class USART {
        public:
            
            USART(
                USART_ID instance, 
                HAL::GPIO::AF::GPIO_AF *_rx, 
                HAL::GPIO::AF::GPIO_AF *_tx
            );

            // Configuration
            void configure_baud_rate(uint32_t sysclock_mhz, uint32_t baud);
            void enable_rs485_driver(HAL::GPIO::AF::GPIO_AF *rtsPin);
            void write_data_IT(const char* data, size_t len);
            void set_cr1_flag(CTRL_REG_1 flg);
            void clear_cr1_flag(CTRL_REG_1 flg);
            void set_cr3_flag(CTRL_REG_3 flg);
        private:
            USART_TypeDef* usartInst = nullptr;
            std::deque<uint8_t> rxBuff {};
            std::deque<uint8_t> txBuff {};
            HAL::GPIO::AF::GPIO_AF *rx, *tx, *rts;
            USART_TypeDef *get_usart_instance(USART_ID target);
    };
}
