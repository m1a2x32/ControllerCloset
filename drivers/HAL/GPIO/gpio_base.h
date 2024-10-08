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
            GPIO_TypeDef *get_port_instance(AVAILABLE_PORTS target);
    };

    namespace INPUT{

        class GPIO_INPUT : public IO {
            public:
                GPIO_INPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
                bool read_state();
        };
    }

    namespace OUTPUT {

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

        class GPIO_OUTPUT : public IO {
            public:
                GPIO_OUTPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
                void set_pin();
                void reset_pin();
                
                void set_output_type(TYPE_REG oTypeReg);
                void set_output_speed(SPEED_REG oSpeedReg);
        };
    }
    
    namespace AF {

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

        class GPIO_AF : public IO {
            public:
                GPIO_AF(AVAILABLE_PORTS _ioPort, uint8_t _ioPin);
                void set_alternate_function(ALTERNTAE_FUNCTIONS nr);
        };
    }
}
