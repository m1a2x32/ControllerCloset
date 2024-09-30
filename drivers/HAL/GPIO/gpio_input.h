#pragma once

#include "gpio_base.h"

namespace HAL::GPIO::INPUT{
    class GPIO_INPUT : private IO {
        public:
            GPIO_INPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
    };
}