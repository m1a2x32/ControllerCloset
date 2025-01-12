#pragma once

#include <stdint.h>

namespace Modbus {
    #pragma pack(push, n)
    struct request_mbus_t {
        uint8_t address;
        uint8_t function;
        uint16_t start_address;
        uint16_t function_variable_byte;
        uint16_t crc;
    };
    struct response_mbus_t {
        uint8_t address;
        uint8_t function;
        uint16_t start_address;
        uint16_t *data; 
        uint8_t data_size;
        uint16_t crc;
    };
    #pragma pack(pop)

    class IClient{
        public:
            IClient(uint8_t slave_address);
            /* Only functions soil sensor supports, add more if needed */
            void read_holding_registers(const uint16_t address,const uint16_t reg_nrs, uint16_t &data, uint8_t &data_size);                         // x03
            void write_holding_register(const uint16_t address, const uint16_t data_to_write, uint16_t &data, uint8_t &data_size);                  // x06
        private:
            uint8_t slave_address;
            virtual void send_request(request_mbus_t *mbus, uint32_t timeout_ms) = 0;
            virtual void receive_response(response_mbus_t *mbus, uint32_t timeout_ms) = 0;
    };
};