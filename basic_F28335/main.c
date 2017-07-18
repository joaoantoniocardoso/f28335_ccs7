/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: Bárbara Coelho, João Antônio Cardoso
 *
 *  Description: Código para testar a placa do Raul
 *
 */

#include "DSP28x_Project.h"
#include "my_buttons.h"
#include "my_leds.h"

//#include "my_epwm_example.h"
#include "my_epwm.h"

void botoes_leds(void);

void main(void)
{

    InitSysCtrl();

    my_buttons_init();
    my_leds_init();
    my_epwm_init();

    InitPieCtrl();

    DINT;   // Disable CPU interrupt

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    for(;;){

        botoes_leds();

    }

}

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
