#include <stm32g070xx.h>
#include <stm32g0xx.h>

#include <stdint.h>

/* Missing to clear register before any bit settings*/
namespace HAL::GPIO{

    typedef enum AVAILABLE_PORTS {
        PORTA = 1,
        PORTB,
        PORTC,
        PORTD,
        PORTF
    };

    typedef enum GPIO_MODES{
        INPUT_MODE   = ~GPIO_MODER_MODE0,
        OUTPUT_MODE  = GPIO_MODER_MODE0_0,
        ANALOG_MODE  = GPIO_MODER_MODE0_1,
        AF_MODE      = GPIO_MODER_MODE0,
    };

    class IO {
        public:
            IO(AVAILABLE_PORTS _ioPort, uint8_t _ioPin){
                port    = get_port(_ioPort);
                pinNr   = _ioPin;
            };

        protected:
            GPIO_TypeDef *port;
            uint8_t pinNr;

            void set_io_type(GPIO_MODES ModeReg){
                if (ModeReg == INPUT_MODE){
                    port->MODER &= ModeReg << (pinNr << 1);
                    return;
                }
                port->MODER     |= ModeReg << (pinNr << 1);
            };

            GPIO_TypeDef *get_port(AVAILABLE_PORTS target){
                switch (target)
                {
                case PORTA:
                    SET_BIT(RCC->CR, RCC_IOPENR_GPIOAEN); // Enable Clock for PORTx
                    return GPIOA;
                case PORTB:
                    SET_BIT(RCC->CR, RCC_IOPENR_GPIOBEN);
                    return GPIOB;
                case PORTC:
                    SET_BIT(RCC->CR, RCC_IOPENR_GPIOCEN);
                    return GPIOC;
                case PORTD:
                    SET_BIT(RCC->CR, RCC_IOPENR_GPIODEN);
                    return GPIOD;
                case PORTF:
                    SET_BIT(RCC->CR, RCC_IOPENR_GPIOFEN);
                    return GPIOF;
                default:
                    return nullptr;
                }
            };
    };
}