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
#include "my_epwm.h"

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
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    InitSysCtrl();

    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    // InitGpio();  // Skipped for this example

    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
    // These functions are in the DSP2833x_EPwm.c file
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    InitPieVectTable();

    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected registers
    //PieVectTable.EPWM1_INT = &epwm1_isr;
    //PieVectTable.EPWM2_INT = &epwm2_isr;
    //PieVectTable.EPWM3_INT = &epwm3_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    // InitPeripherals();  // Not required for this example

    // For this example, only initialize the ePWM

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    // Step 5. User specific code, enable interrupts:

    // Enable CPU INT3 which is connected to EPWM1-3 INT:
    IER |= M_INT3;

    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    for(;;){

        botoes_leds();

    }

}


