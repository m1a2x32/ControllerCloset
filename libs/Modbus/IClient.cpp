#include "IClient.hpp"

namespace Modbus {
    IClient::IClient(uint8_t slave_address){
        this->slave_address = slave_address;
    }

    void IClient::read_holding_registers(const uint16_t address, const uint16_t reg_nrs, uint16_t &data, uint8_t &data_size){
        request_mbus_t mbus = {
            .address = slave_address,
            .function = 0x03,
            .start_address = address,
            .function_variable_byte = reg_nrs,
            .crc = 0x0000
        };
        send_request(&mbus, 1000);
        response_mbus_t response;
        response.data_size = reg_nrs*sizeof(uint16_t);
        receive_response(&response, 1000);
    }

    void IClient::write_holding_register(const uint16_t address, const uint16_t data_to_write, uint16_t &data, uint8_t &data_size){
        request_mbus_t mbus = {
            .address = slave_address,
            .function = 0x06,
            .start_address = address,
            .function_variable_byte = data_to_write,
            .crc = 0x0000
        };
        send_request(&mbus, 1000);
        response_mbus_t response;
        response.data_size = sizeof(uint16_t);
        receive_response(&response, 1000);
    }
}
