/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: joaoantoniocardoso
 */

#include "DSP28x_Project.h"

void main(void)
{
    Uint32 delay;

    InitSysCtrl();

    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    EDIS;

    while(1){
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        for(delay = 0; delay < 2000000; delay++);
    }

}


