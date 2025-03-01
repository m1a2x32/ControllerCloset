#include "Pwm.hpp"

namespace Device::Pwm
{
    using namespace HAL::TIMER;

    Input::Input(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel) 
        : GenericTimer(timer, pin, channel)
    {
    }

    Output::Output(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel) 
        : GenericTimer(timer, pin, channel)
    {
    }
    
    

}
