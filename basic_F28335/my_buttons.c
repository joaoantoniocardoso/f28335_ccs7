/**
 * my_buttons.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_buttons.h"

void my_buttons_init(void)
{
    EALLOW;

    // Configura os pinos para os botões como entrada
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;

    EDIS;
}
