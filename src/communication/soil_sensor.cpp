#include "main.hpp"
#include "usart.hpp"
#include "cmsis_os.h"

using namespace HAL::UART;

USART soilSensorUsart(
    USART_ID::USART_1,
    new HAL::GPIO::AF::GPIO_AF(HAL::GPIO::AVAILABLE_PORTS::PORTD, 5, HAL::GPIO::AF::AF1),// rx
    new HAL::GPIO::AF::GPIO_AF(HAL::GPIO::AVAILABLE_PORTS::PORTD, 6, HAL::GPIO::AF::AF1) // tx
);

void communication_task(void *argument){
    // USART Config
    soilSensorUsart.enable_rs485_driver(new HAL::GPIO::AF::GPIO_AF(HAL::GPIO::AVAILABLE_PORTS::PORTD, 4, HAL::GPIO::AF::AF1));
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
		osDelay(2000);
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