/**
 * my_leds.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_leds.h"


void my_leds_init(void)
{
    EALLOW;

    // Configura os pinos para os leds como saída
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;

    EDIS;
}
