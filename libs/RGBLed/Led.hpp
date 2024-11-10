#pragma once
#include "gpio.hpp"

using namespace HAL::GPIO::OUTPUT;

namespace Device::Led{
    
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        // Default constructor, initializes color to black (all channels are 0)
        Color() : red(0), green(0), blue(0) {}

        // Constructor to easily initialize colors with custom values
        Color(uint8_t r, uint8_t g, uint8_t b)
            : red(r), green(g), blue(b) {}
    };

    namespace Colors {
        const Color RED(255,0,0);
        const Color BLUE(0,0,255);
        const Color GREEN(0,255,0);
    }

    class RGBLed{
        public:
            RGBLed(
                GPIO_OUTPUT *r,
                GPIO_OUTPUT *g, 
                GPIO_OUTPUT *b
            );
            /**
             * Set color automatically sets the target color for the led.
             */
            void set_color(Color color);

            /**
             * Turns off the color without resetting target color.
             */
            void set_off();
        private:
            GPIO_OUTPUT *ledBlue, *ledRed, *ledGreen;
            Color requested_color;

            /**
             * Helper function to update color of leds.
             */
            void update_leds();
    }; 

}


