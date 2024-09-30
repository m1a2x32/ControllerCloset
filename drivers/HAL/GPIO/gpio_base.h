#pragma once

#include "stm32g070xx.h"
#include "stm32g0xx.h"

#include <stdint.h>


namespace HAL::GPIO{

    enum AVAILABLE_PORTS {
        PORTA = 1,
        PORTB,
        PORTC,
        PORTD,
        PORTF
    };

    enum GPIO_MODES{
        INPUT_MODE   = ~GPIO_MODER_MODE0,
        OUTPUT_MODE  = GPIO_MODER_MODE0_0,
        ANALOG_MODE  = GPIO_MODER_MODE0_1,
        AF_MODE      = GPIO_MODER_MODE0,
    };

    enum PUPD_REG{
        NO_PU_PD     = ~GPIO_PUPDR_PUPD0,
        PULL_UP      = GPIO_PUPDR_PUPD0_0,
        PULL_DOWN    = GPIO_PUPDR_PUPD0_1
    };

    class IO {
        public:
            IO(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
            void config_pupd(PUPD_REG reg);
        protected:
            GPIO_TypeDef *port;
            uint8_t pinNr;

            void set_io_type(GPIO_MODES reg);
            GPIO_TypeDef *get_port(AVAILABLE_PORTS target);
    };
}