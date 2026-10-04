#include "Chassis.hpp"

extern "C" void StartChassisTask(void *argument)
{
    uint32_t wake = osKernelGetTickCount();

    for (;;)
    {
        if (dr16_remote.s1 == 1)
        {
        }
        osDelayUntil(wake + 2U);
        wake += 2U;
    }
}