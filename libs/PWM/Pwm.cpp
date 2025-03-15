#include "Pwm.hpp"

using namespace HAL::TIMER;

namespace Device::Pwm
{ /*All PWM configs are for the same fan */

    Input::Input(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel) 
        : GenericTimer(timer, pin, channel)
    {
        set_channel_type(TIMER_TYPE::TIMER_INPUT);
        set_prescaler(2-1);
        set_auto_reload(1066-1);    // 64MHz/1*1066 = 60kHz
        enable_auto_reload();
        enable();
    }

    Output::Output(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel) 
        : GenericTimer(timer, pin, channel)
    {
        set_channel_type(TIMER_TYPE::TIMER_OUTPUT_PWM_M1);
        set_prescaler(2-1);
        set_auto_reload(1066-1);
        enable_auto_reload();
        enable();
    }
    
    

}
