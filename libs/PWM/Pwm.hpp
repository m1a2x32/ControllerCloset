#pragma once
#include "timer.hpp"

namespace Device::Pwm{

class Input : public HAL::TIMER::GenericTimer {
    public:
        Input(HAL::TIMER::AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel);
        void configure_input_timer(uint8_t duty_cycle, uint16_t frequency);
        uint8_t get_dufty_cycle();
};

class Output : public HAL::TIMER::GenericTimer {
    public:
        Output(HAL::TIMER::AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel);
        void configure_output_timer(uint8_t duty_cycle, uint16_t frequency);
        void update_duty_cycle(uint8_t duty_cycle);
};

}