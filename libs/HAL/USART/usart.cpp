#include "usart.hpp"
#include <stdexcept>

using namespace HAL::GPIO::AF;

namespace HAL::UART{

    Usart::Usart(USART_ID instance, HAL::GPIO::AF::GpioAF *_rx, HAL::GPIO::AF::GpioAF *_tx)
        : usartInst(get_usart_instance(instance)), rx(_rx), tx(_tx)
    {

    }

    USART_TypeDef *Usart::get_usart_instance(USART_ID target)
    {
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
            std::logic_error("Select available Usart instance");
            return nullptr;
        }
    }

    void Usart::clear_cr1_flag(CTRL_REG_1 flg)
    {
        CLEAR_BIT(usartInst->CR1, flg);
    }

    void Usart::set_cr1_flag(CTRL_REG_1 flg)
    {
        SET_BIT(usartInst->CR1, flg);
    }

    void Usart::set_cr3_flag(CTRL_REG_3 flg)
    {
        SET_BIT(usartInst->CR3, flg);
    }

    void Usart::enable_rs485_driver(HAL::GPIO::AF::GpioAF *rtsPin)
    {
        rts = rtsPin;
        set_cr3_flag(ENABLE_RS485);
    }

    void Usart::configure_baud_rate(uint32_t sysclock_mhz, uint32_t baud)
    {
        uint32_t brr_value = sysclock_mhz / baud;
        usartInst->BRR     = brr_value;
    }

    BaseType_t Usart::write_data(const uint8_t* data, size_t len, uint32_t timeout_ms)
    {
        configASSERT( txTaskHandle == NULL );
        txTaskHandle = xTaskGetCurrentTaskHandle();

        /* Get ready to send data */
        txBuff.clear();
        for (size_t i = 0; i < len; ++i) 
        {
            txBuff.push_front(data[i]);
        }
        set_cr1_flag(TX_BUFFER_EMPTY_ISR_ENABLE);           // Enable sending
        
        /* Handle timeout */
        BaseType_t notifyResult = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout_ms));
        clear_cr1_flag(TX_BUFFER_EMPTY_ISR_ENABLE);         // Disable sending, in case of timeout
        txTaskHandle = NULL;
        return notifyResult;
    }

    BaseType_t Usart::read_data(uint8_t* data, size_t& len, uint32_t timeout_ms)
    {
        configASSERT( rxTaskHandle == NULL );
        rxTaskHandle = xTaskGetCurrentTaskHandle();
        
        /* Handle timeout */
        BaseType_t notifyResult = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout_ms));
        
        /* Handle data based on notify result */
        if(notifyResult == pdPASS){
            len = rxBuff.size();    // Pass the size of the buffer to the user
            for (size_t i = 0; i < len; ++i) {
                data[i] = rxBuff.front();
                rxBuff.pop_front();
            }
        }
        rxTaskHandle = NULL;

        return notifyResult;
    }

    void Usart::handle_interrupt()
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        /* Send complete flag to verify we are done */
        if (usartInst->ISR & USART_ISR_TC) 
        {
            SET_BIT(usartInst->ICR, USART_ICR_TCCF);
            if(txTaskHandle){                               // Check for task handle not being NULL
                vTaskNotifyGiveFromISR(txTaskHandle, &xHigherPriorityTaskWoken);        
            }
        }

        /* TX task indicates we are ready to send */
        if (usartInst->ISR & USART_ISR_TXE_TXFNF)
        {
            if (!txBuff.empty()){
                uint8_t nextByte = txBuff.front();
                usartInst->TDR = nextByte;                  // Writing data to TDR clears ISR
                txBuff.pop_front();
            } else {
                clear_cr1_flag(TX_BUFFER_EMPTY_ISR_ENABLE); // Disable sending
            }
        }

        /* RX task indicates there is an incoming byte */
        if (usartInst->ISR & USART_ISR_RXNE_RXFNE_Msk) 
        {
            uint8_t incomingByte = usartInst->RDR;          // Reading data from RDR clears ISR
            rxBuff.push_back(incomingByte);
        }

        /* Idle line indicates RX task has finished */
        if(usartInst->ISR & USART_ISR_IDLE) 
        {
            SET_BIT(usartInst->ICR, USART_ICR_IDLECF);      // Clear flag
            if(rxTaskHandle)
            {                               // Check for task handle not being NULL
                vTaskNotifyGiveFromISR(rxTaskHandle, &xHigherPriorityTaskWoken);    
            }
        }

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}