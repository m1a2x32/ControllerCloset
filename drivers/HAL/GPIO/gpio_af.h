#pragma once

#include "gpio_base.h"

namespace HAL::GPIO::AF{
    enum ALTERNTAE_FUNCTIONS {
        AF0 = 0,
        AF1 = 1,
        AF2 = 2,
        AF3 = 3,
        AF4 = 4,
        AF5 = 5,
        AF6 = 6,
        AF7 = 7
    };

    class GPIO_AF : private IO {
        public:
            GPIO_AF(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
            void set_alternate_function(ALTERNTAE_FUNCTIONS nr);
    };
}