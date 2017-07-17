/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: Bárbara Coelho, João Antônio Cardoso
 *
 *  Description: Código para testar os botões da placa do Raul.
 *
 */

#include "DSP28x_Project.h"

// DEFINICOES
#define botao1       GpioDataRegs.GPADAT.bit.GPIO26
#define botao2       GpioDataRegs.GPADAT.bit.GPIO16
#define botao3       GpioDataRegs.GPADAT.bit.GPIO20

#define led1_clear   GpioDataRegs.GPBCLEAR.bit.GPIO48
#define led1_set     GpioDataRegs.GPBSET.bit.GPIO48
#define led2_clear   GpioDataRegs.GPCCLEAR.bit.GPIO86
#define led2_set     GpioDataRegs.GPCSET.bit.GPIO86
#define led3_clear   GpioDataRegs.GPACLEAR.bit.GPIO15
#define led3_set     GpioDataRegs.GPASET.bit.GPIO15

/**
 * Muda o estado dos leds de acordo com o estado dos botões.
 */
void botoes_leds(void)
{
    if (botao1)        led1_clear = 1;
    else               led1_set = 1;

    if (botao2)        led2_clear = 1;
    else               led2_set = 1;

    if (botao3)        led3_clear = 1;
    else               led3_set = 1;
}

void gpio_select(void)
{
    EALLOW;

    GpioCtrlRegs.GPADIR.all = 0;            // GPIO31-00 como entrada, incluindo os botões
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;     // habilita pino 15 como saída, led3

    GpioCtrlRegs.GPBDIR.all = 0;            // GPIO63-32 como entrada
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;     // habilita pino 48 como saída, led1

    GpioCtrlRegs.GPCDIR.all = 0;            // GPIO87-64 como entrada
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;     // habilita pino 86 como saída, led2

    EDIS;
}


void main(void)
{
    InitSysCtrl();

    gpio_select();

    while(1){

        botoes_leds();

    }

}


