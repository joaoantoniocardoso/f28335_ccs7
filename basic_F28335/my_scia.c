/**
 * my_scia.c
 *
 *  Created on: Jul 25, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_scia.h"

/**
 * @brief Sends a string (char array) through serial.
 */
void my_scia_send_string(const char *s)
{
    Uint32 i = 0;
    while(s[i] != '\0'){
        while(!my_scia_txempty);
        my_scia_send_char(s[i++]);
    }
}

/**
 * @brief Sends an unsigned int (Uint16) through serial.
 */
void my_scia_send_uint16(Uint16 num)
{
    #define MAX_LEN         6   // "65536" is 6 characters with NULL terminator
    #define BASE_10         10  // decimal base

    unsigned char index = MAX_LEN - 1;
    char str[ MAX_LEN ];

    str[index] = '\0';          // adds null terminator
    while(index--){
        str[index] = (num % BASE_10) + '0';     // gets each algarism
        num /= BASE_10;                         // prepare the next

        if(!num){                               // finished
            my_scia_send_string(&str[index]);
            break;
        }
    }

    #undef MAX_LEN
    #undef BASE_10
}

/**
 * @brief Sends an unsigned char buffer.
 */
void my_scia_send_buffer(unsigned char *b, Uint32 lenght)
{
    Uint32 i = 0;
    while(i < lenght) my_scia_send_char(b[i++]);
}

/**
 * @brief returns quantity of bytes available in buffer
 */
Uint32 my_scia_bytes_available(void)
{
    // TODO: implement it!!!
    return 0;
}

/**
 * @brief initialize this scia
 */
void my_scia_init(void)
{
    InitSciGpio();

    // TX FIFO configuration
    SciaRegs.SCIFFTX.bit.SCIRST = 1;        // SCI FIFO can resume transmit or receive
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1;      // SCI FIFO enhancements are enabled
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;  // Re-enable transmit FIFO operation
    SciaRegs.SCIFFTX.bit.TXFFST = 0;        // Transmit FIFO is empty.
    SciaRegs.SCIFFTX.bit.TXFFINT = 1;       // TXFIFO interrupt has occurred, read-only bit
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;      // TX FIFO interrupt based on TXFFIVL match (less than or equal to) is disabled
    SciaRegs.SCIFFTX.bit.TXFFIL = 0;        // Transmit FIFO interrupt level bits. (0 is default)

    // RX FIFO configuration
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;   // Re-enable receive FIFO operation
    SciaRegs.SCIFFRX.bit.RXFFST = 0;        // Receive FIFO is empty
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 0;    // Clear RXFFINT flag
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;      // RX FIFO interrupt based on RXFFIVL match (less than or equal to) will be enabled.
    SciaRegs.SCIFFRX.bit.RXFFIL = 0b01111;  // Receive FIFO interrupt level bits. (0 is default)

    // FIFO Configuration -> just set to not use auto-baudrate features
    SciaRegs.SCIFFCT.all = 0x0;

    // Protocol configuration
    SciaRegs.SCICCR.bit.STOPBITS = 0;       // One stop bit
    SciaRegs.SCICCR.bit.PARITY = 0;         // Odd parity
    SciaRegs.SCICCR.bit.PARITYENA = 0;      // Parity disabled; no parity bit for rx or tx
    SciaRegs.SCICCR.bit.LOOPBKENA = 0;      // Loop Back test mode disabled
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;  // Idle-line mode protocol selected
    SciaRegs.SCICCR.bit.SCICHAR = 0b111;    // 8 char bits

    // Baudrate:
    // BRR = ( LSPCLK / Scia_baud ) -1
    // BRR = 121 -> baud = 38400
    // BRR = 243 -> baud = 19200
    // BRB = 487 -> baud = 9600
    SciaRegs.SCIHBAUD = 487 >> 8;           // Highbyte
    SciaRegs.SCILBAUD = 487 & 0xFF;         // Lowbyte

    //
    SciaRegs.SCICTL1.bit.RXERRINTENA = 0;   // Receive error interrupt disabled
    SciaRegs.SCICTL1.bit.SWRESET = 1;       // Relinquish SCI from Reset
    SciaRegs.SCICTL1.bit.TXWAKE = 0;        // Transmit feature is not selected
    SciaRegs.SCICTL1.bit.SLEEP = 0;         // Sleep mode disabled
    SciaRegs.SCICTL1.bit.TXENA = 1;         // Transmitter enabled
    SciaRegs.SCICTL1.bit.RXENA = 1;         // Send received characters to SCIRXEMU and SCIRXBUF

    //
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;    // Enable RXRDY/BRKDT interrupt
    SciaRegs.SCICTL2.bit.TXINTENA = 1;      // Enable TXRDY interrupt

}
