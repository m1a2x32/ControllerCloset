#include "Led.hpp"

// Note: *** Output logic inversed on LEDs ***
namespace Device::Led{

    RGBLed::RGBLed(GPIO_OUTPUT *r, GPIO_OUTPUT *g, GPIO_OUTPUT *b)
       : ledBlue(b),  // Initialize ledBlue with PORTB and pin 7
         ledRed(r),   // Initialize ledRed with PORTB and pin 8
         ledGreen(g),  // Initialize ledGreen with PORTB and pin 9
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
            ledBlue->reset_pin();
        } else {
            ledBlue->set_pin();
        }

        // Set red LED
        if (requested_color.red > 0) {
            ledRed->reset_pin();
        } else {
            ledRed->set_pin();
        }

        // Set green LED
        if (requested_color.green > 0) {
            ledGreen->reset_pin();
        } else {
            ledGreen->set_pin();
        }
    }
}