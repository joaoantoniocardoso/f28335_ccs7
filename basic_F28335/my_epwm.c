/**
 * my_epwm.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_epwm.h"

void my_epwm_init(void)
{
    InitEPwm1Gpio();
    InitEPwm2Gpio();

    InitEPwm1();
    InitEPwm2();

}

void InitEPwm1(void)
{
    EPwm1Regs.TBCTL.bit.CLKDIV =  0;    // CLKDIV = 1
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 1;  // HSPCLKDIV = 2
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;    // up - down mode
    //EPwm1Regs.AQCTLA.all = 0x0006;        // ZRO = set, PRD = clear
    EPwm1Regs.AQCTLA.all = 0x0090;
    EPwm1Regs.TBPRD = 37500;            // 1KHz - PWM signal
    EPwm1Regs.CMPA.half.CMPA = EPwm1Regs.TBPRD / 2;
}

void InitEPwm2(void)
{
    EPwm2Regs.TBCTL.all = 0xC030;
    EPwm2Regs.TBCTL.bit.CLKDIV =  0;    // CLKDIV = 1
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;  // HSPCLKDIV = 2
    EPwm2Regs.TBCTL.bit.CTRMODE = 2;
    EPwm2Regs.TBPRD = 37500;            // 1KHz - PWM
    EPwm2Regs.ETPS.all = 0x0100;
    EPwm2Regs.ETSEL.all = 0x0A00;
}
