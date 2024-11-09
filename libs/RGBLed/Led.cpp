#include "Led.hpp"

// Note: *** Output logic inversed on LEDs ***
namespace Device::Led{

    RGBLed::RGBLed()
       : ledBlue(AVAILABLE_PORTS::PORTB, 7),  // Initialize ledBlue with PORTB and pin 7
         ledRed(AVAILABLE_PORTS::PORTB, 8),   // Initialize ledRed with PORTB and pin 8
         ledGreen(AVAILABLE_PORTS::PORTB, 9),  // Initialize ledGreen with PORTB and pin 9
         requested_color(Color())
    {
       set_off();
    }

    void RGBLed::set_color(Color color){
        requested_color = color;
        update_leds();
    }

    void RGBLed::set_off(){
        requested_color = Color(0, 0, 0);
        update_leds();
    }

    void RGBLed::update_leds() {
        // Set blue LED
        if (requested_color.blue > 0) {
            ledBlue.reset_pin();
        } else {
            ledBlue.set_pin();
        }

        // Set red LED
        if (requested_color.red > 0) {
            ledRed.reset_pin();
        } else {
            ledRed.set_pin();
        }

        // Set green LED
        if (requested_color.green > 0) {
            ledGreen.reset_pin();
        } else {
            ledGreen.set_pin();
        }
    }
}