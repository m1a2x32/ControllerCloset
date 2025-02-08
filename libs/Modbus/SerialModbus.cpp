#include "SerialModbus.hpp"

namespace Modbus {

    SerialClient::SerialClient(uint8_t slave_address, HAL::UART::Usart *_uart) : IClient(slave_address)
    {
        uart = _uart;
    }

    mbus_err SerialClient::send_request(request_mbus_t *mbus, uint32_t timeout_ms)
    {
        mbus_err ret_err = MBUS_ERR_NONE;

        return ret_err;
    }

    mbus_err SerialClient::receive_response(response_mbus_t *mbus, uint32_t timeout_ms)
    {
        mbus_err ret_err = MBUS_ERR_NONE;

        return ret_err;
    }
}
