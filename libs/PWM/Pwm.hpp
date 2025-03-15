#pragma once
#include "timer.hpp"

namespace Device::Pwm{

class Input : public HAL::TIMER::GenericTimer {
    public:
        Input(HAL::TIMER::AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel);
        void start();
        void stop();
        uint8_t get_duty_cycle();
    private:
        float _duty_cycle;
};

class Output : public HAL::TIMER::GenericTimer {
    public:
        Output(HAL::TIMER::AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel);
        void update_duty_cycle(uint8_t duty_cycle);
    private:
        float _duty_cycle;
};

}