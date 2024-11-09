#pragma once
#include "gpio_base.hpp"

extern HAL::GPIO::OUTPUT::GPIO_OUTPUT ledBlue, ledRed, ledGreen;

extern void reset_all_leds();