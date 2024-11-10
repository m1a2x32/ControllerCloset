#include "main.hpp"
#include "usart.hpp"
#include "cmsis_os.h"

using namespace HAL::UART;

USART soilSensorUsart;

void communication_task(void *pvParameters){
    // GPIO Config
    auto usartTx  = std::make_unique<HAL::GPIO::AF::GPIO_AF>(HAL::GPIO::AVAILABLE_PORTS::PORTD, 8);
    auto usartRx  = std::make_unique<HAL::GPIO::AF::GPIO_AF>(HAL::GPIO::AVAILABLE_PORTS::PORTD, 9);
    auto usartRts = std::make_unique<HAL::GPIO::AF::GPIO_AF>(HAL::GPIO::AVAILABLE_PORTS::PORTD, 12);
    usartTx->set_alternate_function(HAL::GPIO::AF::AF7);
    usartRx->set_alternate_function(HAL::GPIO::AF::AF7);
    usartRts->set_alternate_function(HAL::GPIO::AF::AF7);
    
    // USART Config
    soilSensorUsart = USART(USART_ID::USART_1, std::move(usartRx), std::move(usartTx));    
    soilSensorUsart.enable_rs485_driver(std::move(usartRts));
    soilSensorUsart.configure_baud_rate(SystemCoreClock, 115200);

    soilSensorUsart.set_cr1_flag(CTRL_REG_1::ENABLE_RX);
    soilSensorUsart.set_cr1_flag(CTRL_REG_1::ENABLE_TX);
    soilSensorUsart.set_cr1_flag(CTRL_REG_1::RX_NOT_EMPTY_ISR);
    soilSensorUsart.set_cr1_flag(CTRL_REG_1::TX_COMPLETE_ISR);
    soilSensorUsart.set_cr1_flag(CTRL_REG_1::TX_EMPTY_ISR);
    soilSensorUsart.set_cr1_flag(CTRL_REG_1::ENABLE_USART);

    NVIC_EnableIRQ(USART3_4_IRQn);
    NVIC_SetPriority(USART3_4_IRQn, 3);

    while(1){
		vTaskDelay(pdMS_TO_TICKS(200));
    }
}

extern "C" void USART3_4_IRQHandler(){
    // Todo: handle interrupts
    uint32_t flags = soilSensorUsart.usartInst->ISR;
    if(flags & USART_ISR_TXFE){
        uint8_t sendByte = soilSensorUsart.txBuff.back();
        soilSensorUsart.usartInst->TDR = sendByte ;// Writing to reg clears byte
        soilSensorUsart.txBuff.pop_back();
    }

    if(flags & USART_ISR_RXNE_RXFNE){
        uint8_t receivedByte = soilSensorUsart.usartInst->RDR; // Reading from reg clears byte
        soilSensorUsart.rxBuff.push_back(receivedByte);
    }
    
    if(flags & USART_ISR_TXE_TXFNF){
        /* Transmit flag*/
        CLEAR_BIT(soilSensorUsart.usartInst->ISR, USART_ISR_TC);  // Clear TC flag if needed    
    } 
}