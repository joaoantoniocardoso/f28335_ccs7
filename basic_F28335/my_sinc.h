/**
 * my_sinc.h
 *
 *  Created on: Sep 28, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_SINC_H_
#define MY_SINC_H_

#include "DSP28x_Project.h"

#define sinc1 GpioDataRegs.GPBDAT.bit.GPIO33
#define sinc2 GpioDataRegs.GPADAT.bit.GPIO31
#define sinc3 GpioDataRegs.GPADAT.bit.GPIO29

void my_sinc_init(void);

#endif /* MY_SINC_H_ */
