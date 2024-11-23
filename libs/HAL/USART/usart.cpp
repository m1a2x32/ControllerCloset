#include "usart.hpp"
#include <stdexcept>

using namespace HAL::GPIO::AF;

namespace HAL::UART{

    USART::USART(USART_ID instance, HAL::GPIO::AF::GPIO_AF *_rx, HAL::GPIO::AF::GPIO_AF *_tx)
        : usartInst(get_usart_instance(instance)), rx(_rx), tx(_tx)
    {

    }

    USART_TypeDef *USART::get_usart_instance(USART_ID target){
        switch (target)
        {
        case USART_1:
            SET_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN);
            return USART1;
        case USART_2:
            SET_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN);
            return USART2;
        case USART_3:
            SET_BIT(RCC->APBENR1, RCC_APBENR1_USART3EN);
            return USART3;
        case USART_4:
            SET_BIT(RCC->APBENR1, RCC_APBENR1_USART4EN);
            return USART4;
        default:
            std::logic_error("Select available USART instance");
            return nullptr;
        }
    }

    void USART::clear_cr1_flag(CTRL_REG_1 flg){
        CLEAR_BIT(usartInst->CR1, flg);
    }

    void USART::set_cr1_flag(CTRL_REG_1 flg){
        SET_BIT(usartInst->CR1, flg);
    }

    void USART::set_cr3_flag(CTRL_REG_3 flg){
        SET_BIT(usartInst->CR3, flg);
    }

    void USART::enable_rs485_driver(HAL::GPIO::AF::GPIO_AF *rtsPin){
        rts = rtsPin;
        set_cr3_flag(ENABLE_RS485);
    }

    void USART::configure_baud_rate(uint32_t sysclock_mhz, uint32_t baud){
        uint32_t brr_value = sysclock_mhz / baud;
        usartInst->BRR     = brr_value;
    }

    void USART::write_data_IT(const char* data, size_t len){
        txBuff.clear();
        for (size_t i = 0; i < len; ++i) {
            txBuff.push_front(data[i]); // Push data to the front of the deque
        }
        set_cr1_flag(TX_BUFFER_EMPTY_ISR_ENABLE);
    }

    void USART::handle_interrupt(){
        // Transmission Complete (TC) check
        if (usartInst->ISR & USART_ISR_TC)
        {
            // Transmission complete, clear the flag
            SET_BIT(usartInst->ICR, USART_ICR_TCCF);
        }

        if (usartInst->ISR & USART_ISR_TXE_TXFNF)
        {
            // If there is more data to send, transmit the next byte
            if (!txBuff.empty()){
                uint8_t nextByte = txBuff.front();
                usartInst->TDR = nextByte;        // Load next byte into the data register
                txBuff.pop_front();               // Remove the byte from the queue
            } else {
                clear_cr1_flag(TX_BUFFER_EMPTY_ISR_ENABLE);
            }
        }
    }
}