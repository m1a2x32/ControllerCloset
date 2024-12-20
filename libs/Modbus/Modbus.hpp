#include "usart.hpp"

namespace Modbus {

    #pragma pack(push, 1)
    struct mbus_t {
        uint8_t address;
        uint8_t function;
        uint16_t *data;
        size_t data_len;
        uint16_t crc;
    };
    #pragma pop()

    using namespace HAL::UART;
    class IClient{
        public:
            virtual void read_coils(uint16_t address, uint16_t coil_nrs) = 0;                                   // x01
            virtual void read_discrete_inputs(uint16_t address, uint16_t reg_nrs) = 0;                          // x02
            virtual void read_holding_registers(uint16_t address, uint16_t reg_nrs) = 0;                        // x03
            virtual void read_input_registers(uint16_t address, uint16_t reg_nrs) = 0;                          // x04
            virtual void write_coil(uint16_t address, uint16_t coil_addr, uint16_t to_write) = 0;               // x05
            virtual void write_holding_register(uint16_t address, uint16_t reg_addr, uint16_t to_write) = 0;    // x06
    };
};