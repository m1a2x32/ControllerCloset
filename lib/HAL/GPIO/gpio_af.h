#include <gpio_base.h>
namespace HAL::GPIO::AF{
    typedef enum ALTERNTAE_FUNCTIONS {
        AF0 = 1,
        AF1,
        AF2,
        AF3,
        AF4,
        AF5,
        AF6,
        AF7
    };

    class GPIO_AF : private IO {
        public:
            GPIO_AF(AVAILABLE_PORTS _ioPort, uint8_t _ioPin) : IO(_ioPort, _ioPin){
                set_io_type(GPIO::GPIO_MODES::AF_MODE);
            }
    };
}