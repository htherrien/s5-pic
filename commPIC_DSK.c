/**************************************************************************
Version 1.0
 
Auteur : Hugo Daniel, Cedrik Maillette
Date de cr√©ation : 29/11/2017
 
Liste de modification:
1. ModifiÈ par: Hugo Daniel, Cedrik Maillette
2. ModifiÈ par: Hugo Therrien
 
Description : Fonctions en rapport avec la communication PIC DSK
Propri√©t√© : Les S de Sherbrooke
**************************************************************************/


// Librairies
#include "commPIC_DSK.h"
#include "LCD_SPI.h"

// Variables 

void configPIC_DSK(void)
{
    configUART();
    configIntUART();
}

void configUART(void)
{
    // PPS-Lite configuration of GPIO pins to EUSART peripherial
    //RPINR0_1<7:4> = 0x60    --> RP26 = U1TX (output)
    //RPINR0_1<3:0> = 0x06    --> RP27 = U1RX (input)
    RPINR0_1 &= 0x00;
    RPINR0_1 |= 0x66; 
    //RPOR26_27<7:4> = 0x10    --> U1TX = RP26 (output)
    //RPOR26_27<3:0> = 0x01    --> U1RX = RP27 (input)
    RPOR26_27 |= 0x11; 
    
    // configuration des pins
    TRISDbits.TRISD6 = 0;   //TX set output
    TRISDbits.TRISD7 = 1;   //RX set input

    // configuration communication UART
    SPBRG1 = BAUDRATE;       // Set baud rate pour 115.2kBaud
    SPBRGH1 = 0;
    TXSTA1bits.BRGH = 1;     // High speed
    TXSTA1bits.TXEN = 1;     // Transmit is enabled
    RCSTA1bits.SPEN = 1;     // Serial port is enabled
    RCSTA1bits.CREN = 1;     // Enables receiver
    BAUDCON1bits.BRG16 = 1;  // 16-bit Baud Rate Generator 
   
    
}

void configIntUART(void)
{
    // configuration Interrupt
    INTCONbits.PEIE = 1;    // Enables all unmasked peripheral interrupts
    PIE1bits.RC1IE = 1;     // Enables the EUSART1 receive interrupt
    //PIE1bits.TX1IE = 1;     // Enables the EUSART1 transmit interrupt
    INTCONbits.GIE = 1;     // Enables all unmasked interrupts
}


unsigned char lectureCharUART(void)
{
    unsigned char trameRecueDSK = RCREG1; // Lie la valeur du buffer de reception
    RCREG1 = 0x00; //POURQUOI? Descendre le flag RCIF1 je pense
    return trameRecueDSK;
}

void ecrireCharUART(unsigned char caractere)
{
    while(!TXSTA1bits.TRMT){}     // Attendre que l'Ècriture sois fini
    TXREG1 = caractere; // Ecrit dans le buffer d'envoi
    /*
    if(PIR1bits.RC1IF == 1) // Bit de flag indiquant que le buffer de reception UART est plein
     {
         putStringLCD("Bob");
     }
    */
}

int ecrireMessageUART(uint8_t message[])
{
    int index = 0;
    do
    {
        while(!TXSTA1bits.TRMT){};
        TXREG1 = message[index];
        index++;
    }while(message[index]);
}
