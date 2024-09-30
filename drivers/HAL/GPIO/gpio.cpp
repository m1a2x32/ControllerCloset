#include "gpio_input.h"
#include "gpio_output.h"
#include "gpio_af.h"

namespace HAL::GPIO {

    IO::IO(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) {
        port    = get_port(_ioPort);
        pinNr   = _ioPin;
    }

    void IO::config_pupd(PUPD_REG reg){
        CLEAR_BIT(port->PUPDR, (reg << (pinNr << 1)));
        if (reg == NO_PU_PD) return;

        SET_BIT(port->PUPDR, (reg << (pinNr << 1)));
    }

    void IO::set_io_type(GPIO_MODES reg){
        CLEAR_BIT(port->MODER, (reg << (pinNr << 1)));
        if (reg == INPUT_MODE) return;

        SET_BIT(port->MODER, (reg << (pinNr << 1)));
    }

    GPIO_TypeDef *IO::get_port(AVAILABLE_PORTS target) {
        switch (target) {
            case PORTA:
                SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); // Enable Clock for PORTx
                return GPIOA;
            case PORTB:
                SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
                return GPIOB;
            case PORTC:
                SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
                return GPIOC;
            case PORTD:
                SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN); 
                return GPIOD;
            case PORTF:
                SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
                return GPIOF;
            default:
                return nullptr;
        }
    }
}

namespace HAL::GPIO::INPUT {
    GPIO_INPUT::GPIO_INPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin): IO(_ioPort, _ioPin){
        set_io_type(GPIO_MODES::INPUT_MODE);
    }
    
    bool GPIO_INPUT::read_state(){
        return (port->IDR & (1 << pinNr)) != 0;
    }
}

namespace HAL::GPIO::OUTPUT{
    GPIO_OUTPUT::GPIO_OUTPUT(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) : IO(_ioPort, _ioPin){
        set_io_type(GPIO_MODES::OUTPUT_MODE);
    }

    void GPIO_OUTPUT::set_pin(){
        // Todo: double check this work, if not bsrr reg
        SET_BIT(port->ODR, (1 << pinNr));
    }

    void GPIO_OUTPUT::reset_pin(){
        CLEAR_BIT(port->ODR, (1 << pinNr));
    }

    void GPIO_OUTPUT::set_output_type(TYPE_REG oTypeReg){
        CLEAR_BIT(port->OTYPER, (oTypeReg << pinNr));
        if (oTypeReg == PUSH_PULL) return;

        SET_BIT(port->OTYPER, (oTypeReg << pinNr));
    }

    void GPIO_OUTPUT::set_output_speed(SPEED_REG oSpeedReg){
        CLEAR_BIT(port->OSPEEDR, (oSpeedReg << (pinNr << 1)));
        if(oSpeedReg == VERY_LOW_SPEED) return;

        SET_BIT(port->OSPEEDR, (oSpeedReg << (pinNr << 1)));
    }
}

namespace HAL::GPIO::AF{
    GPIO_AF::GPIO_AF(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) : IO(_ioPort, _ioPin){
        set_io_type(GPIO_MODES::AF_MODE);
    }

    void GPIO_AF::set_alternate_function(ALTERNTAE_FUNCTIONS nr){
        if (pinNr <= 7){
            CLEAR_BIT(port->AFR[0], (nr << (pinNr << 2)));
            if(nr == AF0) return;

            SET_BIT(port->AFR[0], (nr << (pinNr << 2)));
        } else {
            CLEAR_BIT(port->AFR[1], (nr << (pinNr << 2)));
            if(nr == AF0) return;

            SET_BIT(port->AFR[1], (nr << (pinNr << 2)));
        }
        
    }
}