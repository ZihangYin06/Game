#ifndef _LIFT_HPP
#define _LIFT_HPP

#include "cmsis_os.h"
#include "LIFT_Task.hpp"
#include "bsp_dr16.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void StartLIFTTask(void *argument);

#ifdef __cplusplus
}
#endif

#endif