/**
 * my_leds.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "DSP28x_Project.h"

#define led1_clear   GpioDataRegs.GPBCLEAR.bit.GPIO48
#define led1_set     GpioDataRegs.GPBSET.bit.GPIO48
#define led2_clear   GpioDataRegs.GPCCLEAR.bit.GPIO86
#define led2_set     GpioDataRegs.GPCSET.bit.GPIO86
#define led3_clear   GpioDataRegs.GPACLEAR.bit.GPIO15
#define led3_set     GpioDataRegs.GPASET.bit.GPIO15

void my_leds_init(void);

#endif /* MY_LEDS_H_ */
