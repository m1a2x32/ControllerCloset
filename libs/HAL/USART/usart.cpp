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

    void USART::set_cr1_flag(CTRL_REG_1 flg){
        SET_BIT(usartInst->CR1, flg);
    }


    void USART::enable_rs485_driver(HAL::GPIO::AF::GPIO_AF *rtsPin){
        rts = rtsPin;
        SET_BIT(usartInst->CR3, USART_CR3_DEM);
    }

    void USART::configure_baud_rate(uint32_t sysclock_mhz, uint32_t baud){
        uint32_t brr_value = sysclock_mhz / baud;
        usartInst->BRR     = brr_value;
    }

}