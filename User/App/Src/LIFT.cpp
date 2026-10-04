#include "LIFT.hpp"

extern "C" void StartLIFTTask(void *argument)
{
    uint32_t wake = osKernelGetTickCount();
    LIFT_Init();

    for (;;)
    {
        if (dr16_remote.s2 == 1)
        {
        }
        osDelayUntil(wake + 2U);
        wake += 2U;
    }
}