#pragma once

#include "usart.hpp"
#include "IClient.hpp"

namespace Modbus {

    class SerialClient : public IClient {
        public:
            SerialClient(uint8_t slave_address, HAL::UART::USART *_uart);
        private:
            HAL::UART::USART *uart;
            mbus_err send_request(request_mbus_t *mbus, uint32_t timeout_ms) override;
            mbus_err receive_response(response_mbus_t *mbus, uint32_t timeout_ms) override;
    };
}