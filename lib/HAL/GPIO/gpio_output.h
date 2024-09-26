#include <gpio_base.h>

namespace HAL::GPIO::OUTPUT{
    typedef enum TYPE_REG{
        OPEN_DRAIN      = GPIO_OTYPER_OT0,
        PUSH_PULL       = ~GPIO_OTYPER_OT0,
    };

    typedef enum SPEED_REG{
        VERY_LOW_SPEED  = ~GPIO_OSPEEDR_OSPEED0,
        LOW_SPEED       = GPIO_OSPEEDR_OSPEED0_0,
        HIGH_SPEED      = GPIO_OSPEEDR_OSPEED0_1,
        VERY_HIGH_SPEED = GPIO_OSPEEDR_OSPEED0,
    };

    class GPIO_OUTPUT : private IO {
        public:
            GPIO_OUTPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) : IO(_ioPort, _ioPin){
                set_io_type(GPIO::GPIO_MODES::OUTPUT_MODE);
            }

            void set_output_type(TYPE_REG oTypeReg){
                if (oTypeReg == PUSH_PULL){
                    port->OTYPER        &= (oTypeReg << pinNr);        
                    return;
                }
                port->OTYPER            |= (oTypeReg << pinNr);
            }

            void set_output_speed(SPEED_REG oSpeedReg){
                if(oSpeedReg == VERY_LOW_SPEED){
                    port->OSPEEDR &= (oSpeedReg << (pinNr << 1));
                    return;
                }
                port->OSPEEDR |= (oSpeedReg << (pinNr << 1));
            }
    };
}