#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include <stm32g070xx.h>
#include <stm32g0xx.h>

extern "C" void app_main();
extern void communication_task(void *argument);

#endif