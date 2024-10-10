#include <usart.h>
#include <stdexcept>

using namespace HAL::GPIO::AF;

namespace HAL::UART{

    USART::USART(AVAILABLE_USARTS instance, GPIO_AF *_rx, GPIO_AF *_tx){
        if ((_tx == nullptr) | (_rx == nullptr)) std::logic_error("Pins not assigned");
        tx = _tx;
        rx = _rx;

        usartInst = get_usart_instance(instance);
        this->disable_usart();
    }

    USART_TypeDef *USART::get_usart_instance(AVAILABLE_USARTS target){
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

    void USART::enable_usart(){
        SET_BIT(usartInst->CR1, USART_CR1_UE);
    }

    void USART::disable_usart(){
        CLEAR_BIT(usartInst->CR1, USART_CR1_UE);
    }

    void USART::enable_rs485_driver(GPIO_AF *rtsPin){
        if(rtsPin == nullptr) std::logic_error("RTS pin not assigned");
        rts = rtsPin;
        SET_BIT(usartInst->CR3, USART_CR3_DEM);
    }

    void USART::configure_baud_rate(uint32_t baud){

    }
}