#pragma once

#include <stdint.h>
#include <stm32g070xx.h>
#include <stm32g0xx.h>

#include "FreeRTOS.h"
#include "cmsis_os2.h"

extern void communication_task(void *argument);
