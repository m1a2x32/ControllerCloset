#pragma once

#include "gpio.hpp"
#include <stdint.h>
#include <memory>


namespace HAL::TIMER 
{
    enum CTRL_REG1
    {
        TIMER_AUTO_RELOAD_EN        = TIM_CR1_ARPE,
        TIMER_ONE_PULSE_MODE        = TIM_CR1_OPM,
        TIMER_UPDATE_REQUEST_SRC    = TIM_CR1_URS,
        TIMER_COUNTER_ENABLE        = TIM_CR1_CEN,
    };

    enum CCER_REG
    {
        TIMER_OUTPUT_ENABLE         = TIM_CCER_CC1E,
        TIMER_OUTPUT_POLARITY       = TIM_CCER_CC1P,
    };

    enum TIMER_TYPE
    {
        TIMER_OUTPUT = TIM_CCMR1_CC1S_Pos,
        TIMER_INPUT = TIM_CCMR1_CC1S_0
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
            void enable();
        protected:
            void set_ccer_reg(CCER_REG reg, uint8_t channel);
            void set_ccmr_reg1(uint8_t channel, uint8_t reg);
            void set_ctrl_reg1(CTRL_REG1 reg);
            
            TIM_TypeDef* _timInst;
            std::shared_ptr<HAL::GPIO::AF::GpioAF> _pin;
            uint8_t _channel;
    };
}
