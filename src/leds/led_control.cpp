#include <led_control.h>

// Note: *** Output logic inversed on LEDs ***

HAL::GPIO::OUTPUT::GPIO_OUTPUT ledBlue(HAL::GPIO::AVAILABLE_PORTS::PORTB, 7);
HAL::GPIO::OUTPUT::GPIO_OUTPUT ledRed(HAL::GPIO::AVAILABLE_PORTS::PORTB, 8);
HAL::GPIO::OUTPUT::GPIO_OUTPUT ledGreen(HAL::GPIO::AVAILABLE_PORTS::PORTB, 9);

void reset_all_leds(void){
    ledRed.set_pin();
    ledBlue.set_pin();
    ledGreen.set_pin();
}