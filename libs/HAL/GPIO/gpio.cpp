#include "gpio.hpp"
#include <stdexcept>

namespace HAL::GPIO {

    IO::IO(AVAILABLE_PORTS _ioPort, uint8_t _ioPin)
    {
        if(_ioPin > 15) std::range_error("Pin number not available");
        port    = get_port_instance(_ioPort);
        pinNr   = _ioPin;
    }

    void IO::config_pupd(PUPD_REG reg)
    {
        MODIFY_REG(port->PUPDR, (0x3UL << (pinNr << 1)), (reg << (pinNr << 1)));
    }

    void IO::set_io_type(GPIO_MODES reg)
    {
        MODIFY_REG(port->MODER, (0x3UL << (pinNr << 1)), (reg << (pinNr << 1)));
    }

    GPIO_TypeDef *IO::get_port_instance(AVAILABLE_PORTS target) 
    {
        switch (target) 
        {
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
                std::logic_error("GPIO not available");
                return nullptr;
        }
    }

    namespace INPUT 
    {

        GpioInput::GpioInput(AVAILABLE_PORTS _ioPort, uint8_t _ioPin): IO(_ioPort, _ioPin)
        {
            set_io_type(GPIO_MODES::INPUT_MODE);
        }
        
        bool GpioInput::read_state()
        {
            return (port->IDR & (1 << pinNr)) != 0;
        }
    }

    namespace OUTPUT 
    {

        GpioOutput::GpioOutput(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) : IO(_ioPort, _ioPin)
        {
            set_io_type(GPIO_MODES::OUTPUT_MODE);
        }

        void GpioOutput::set_pin()
        {
            // Todo: double check this work, if not bsrr reg
            SET_BIT(port->BSRR, (1 << pinNr));
        }

        void GpioOutput::reset_pin()
        {
            SET_BIT(port->BSRR, (1 << (pinNr + 16)));
        }

        bool GpioOutput::read_output()
        {
            return READ_BIT(port->ODR, (1 << pinNr));
        }

        void GpioOutput::toggle_pin()
        {
            read_output() == true ? reset_pin() : set_pin();
        }

        void GpioOutput::set_output_type(TYPE_REG oTypeReg)
        {
            MODIFY_REG(port->OTYPER, (0x1UL << pinNr), (oTypeReg << pinNr));
        }

        void GpioOutput::set_output_speed(SPEED_REG oSpeedReg)
        {
            MODIFY_REG(port->OSPEEDR, (0x3UL << (pinNr << 1)), (oSpeedReg << (pinNr << 1)));
        }
    }

    namespace AF 
    {
        GpioAF::GpioAF(AVAILABLE_PORTS _ioPort, uint8_t _ioPin, ALTERNTAE_FUNCTIONS nr) : IO(_ioPort, _ioPin)
        {
            set_io_type(GPIO_MODES::AF_MODE);
            set_alternate_function(nr);
        }

        void GpioAF::set_alternate_function(ALTERNTAE_FUNCTIONS nr)
        {
            if (pinNr <= 7)
            {
                MODIFY_REG(port->AFR[0], (0x7UL << (pinNr << 2)), (nr << (pinNr << 2)));
            } 
            else 
            {
                uint8_t pin_to_write = pinNr - 7;
                MODIFY_REG(port->AFR[1], (0x7UL << (pin_to_write << 2)), (nr << (pin_to_write << 2)));
            }
        }
    }
}
