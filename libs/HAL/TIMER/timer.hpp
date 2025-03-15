#pragma once

#include "gpio.hpp"
#include <stdint.h>
#include <memory>


namespace HAL::TIMER 
{
    enum TIMER_TYPE
    {
        TIMER_OUTPUT = TIM_CCMR1_CC1S_Pos,
        TIMER_INPUT = TIM_CCMR1_CC1S_0,
        TIMER_OUTPUT_PWM_M1 = TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1,
    };

    enum AVAILABLE_TIMERS
    { // We only need timer 1 for this project
        TIMER1 = 1,
    };

    class GenericTimer
    {
        public:
            GenericTimer(AVAILABLE_TIMERS timer, std::shared_ptr<HAL::GPIO::AF::GpioAF> pin, uint8_t channel);
            void set_auto_reload(uint16_t value);
            void set_prescaler(uint16_t value);
            void set_channel_type(TIMER_TYPE type);
            void enable_auto_reload();
            void enable();
            void disable();
        protected:            
            TIM_TypeDef* _timInst;
            std::shared_ptr<HAL::GPIO::AF::GpioAF> _pin;
            uint8_t _channel;
    };
}
