#include "SerialModbus.hpp"

namespace Modbus {

    SerialClient::SerialClient(uint8_t slave_address, HAL::UART::USART *_uart) : IClient(slave_address)
    {
        uart = _uart;
    }

    void SerialClient::send_request(request_mbus_t *mbus, uint32_t timeout_ms){
        
    }

    void SerialClient::receive_response(response_mbus_t *mbus, uint32_t timeout_ms){
        
    }
}
