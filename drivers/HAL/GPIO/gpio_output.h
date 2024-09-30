#pragma once

#include "gpio_base.h"

namespace HAL::GPIO::OUTPUT{
    enum TYPE_REG{
        OPEN_DRAIN      = GPIO_OTYPER_OT0,
        PUSH_PULL       = ~GPIO_OTYPER_OT0,
    };

    enum SPEED_REG{
        VERY_LOW_SPEED  = ~GPIO_OSPEEDR_OSPEED0,
        LOW_SPEED       = GPIO_OSPEEDR_OSPEED0_0,
        HIGH_SPEED      = GPIO_OSPEEDR_OSPEED0_1,
        VERY_HIGH_SPEED = GPIO_OSPEEDR_OSPEED0,
    };

    class GPIO_OUTPUT : private IO {
        public:
            GPIO_OUTPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
            void set_pin();
            void reset_pin();
            
            void set_output_type(TYPE_REG oTypeReg);
            void set_output_speed(SPEED_REG oSpeedReg);
    };
}