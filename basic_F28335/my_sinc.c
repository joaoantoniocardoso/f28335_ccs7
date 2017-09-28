/**
 * my_sinc.c
 *
 *  Created on: Sep 28, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_sinc.h"

/**
 * @brief inicializa o GPIO dos sinais de sincronismo
 */
void my_sinc_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     //sinc3
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 0;     //sinc2
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;     //sinc1
    EDIS;
}
