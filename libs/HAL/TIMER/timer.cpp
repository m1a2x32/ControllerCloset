#include "timer.hpp"
#include "gpio.hpp"
#include <stdexcept>

namespace HAL::TIMER 
{

    GenericTimer::GenericTimer(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel)
        : _pin(std::move(pin)) 
        , _channel(channel)
    {
        if (channel <= 0) std::range_error("Channel must be greater than 0");
        
        switch(timer)
        {
            case AVAILABLE_TIMERS::TIMER1:
                SET_BIT(RCC->APBENR2, RCC_APBENR2_TIM1EN);
                _timInst = TIM1;
                _timInst->DIER |= TIM_DIER_UIE; // Enable update interrupt
                _timInst->DIER |= (TIM_DIER_CC1IE_Pos << channel); // Enable channel to generate interrupt
                break;
            default:
                std::range_error("Timer not available");
        }
    };

    void GenericTimer::set_channel_type(TIMER_TYPE type)
    {
        if (_channel <= 2){
            _timInst->CCMR1 |= (type << ((_channel - 1) * 8)); // channel 1 = pos0, channel 2=  pos8
            return;
        }
        _timInst->CCMR2     |= (type << ((_channel - 3) * 8)); // channel 3 = pos0, channel 4=  pos8
    }

    void GenericTimer::enable()
    {
        SET_BIT(_timInst->CR1, TIM_CR1_CEN);
    }

    void GenericTimer::disable()
    {
        CLEAR_BIT(_timInst->CR1, TIM_CR1_CEN);
    }

    void GenericTimer::enable_auto_reload()
    {
        SET_BIT(_timInst->CR1, TIM_CR1_ARPE);
    }

}
