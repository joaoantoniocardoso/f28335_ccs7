/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: Bárbara Coelho, João Antônio Cardoso
 *
 *  Description: Código para testar a placa do Raul
 *
 *  References: http://www.ti.com/product/TMS320F28335/technicaldocuments
 *
 */

#include "DSP28x_Project.h"
#include "my_buttons.h"
#include "my_leds.h"
#include "my_adc.h"
#include "my_epwm.h"
#include "my_scia.h"
#include "my_sinc.h"

#define MY_DEBUG_

// Variáveis globais
Uint32 dt = 0;

void serial_debug(void);
void botoes_leds(void);
inline void sinc(void);

void main(void)
{

    DINT;   // Disable Global interrupt

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // É necessário para as funções que utilizam macros dos .asm, como o InitAdc.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
    InitFlash();    // call InitFlash in RAM (SARAM - L0)

    InitSysCtrl();

    InitPieCtrl();
    InitPieVectTable();

    my_buttons_init();
    my_sinc_init();
    my_leds_init();
    my_epwm_init();
    my_adc_init();

#ifdef MY_DEBUG_
    my_scia_init();
#endif

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    for(;;){
        //botoes_leds();

#ifdef MY_DEBUG_
        serial_debug();
#endif

        sinc();

        DELAY_US(2500);
    }

}

/**
 * @brief utiliza o sinal de sincronismo para ligar um led (utilizado para teste)
 */
inline void sinc(void)
{
    if(sinc1) led1_set = 1;
    else led1_clear = 1;

    if(sinc2) led2_set = 1;
    else led2_clear = 1;

    if(sinc3) led3_set = 1;
    else led3_clear = 1;
}

/**
 * @brief envia dados de debug via serial
 */
void serial_debug(void)
{
    my_scia_send_string("dt: ");
    my_scia_send_uint16(dt);
    my_scia_send_string("\tADC0: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT0);
    my_scia_send_string("\tADC1: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT1);
    my_scia_send_string("\tADC2: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT2);
    my_scia_send_string("\tADC3: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT3);
    my_scia_send_string("\r\n");
}

/**
 * Muda o estado dos leds de acordo com o estado dos botões.
 */
void botoes_leds(void)
{
    if (botao1)        led1_clear = 1;
    else{
        led1_set = 1;
        if(dt > 0) dt--;
    }

    if (botao2)        led2_clear = 1;
    else{
        led2_set = 1;
        if(dt < 1200) dt++;
    }

    if (botao3)        led3_clear = 1;
    else{
        led3_set = 1;
        dt=0;
    }

    // aplica dutycycle nos epwms 1 e 2
    epwm1_set_dt(dt);
    epwm2_set_dt(dt);

}
