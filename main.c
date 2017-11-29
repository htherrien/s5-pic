/**************************************************************************
Version 1.1
 
Auteur : Danae Dufour-Forget, Franck Laouhap
Date de création : 10/2017
 
Liste de modification:
1. Modifé par: Hugo Daniel et Cedrik Maillette  Date: 29/11/2017
 
Description : Fichier main pour le PIC
Propriété : Les S de Sherbrooke
**************************************************************************/

// Librairies
#include "LCD_SPI.h"
#include "commPIC_DSK.h"
 
//Variables
int flag_nouvelleTrameDSK = 0; // Flag indiquant qu'une nouvelle tramme est arrive sur le DSK
int flag_ecrireTrameDSK = 1; // Flag indiquant qu'une valeur est prete a etre ecrite au DSK
int trameRecueDSK = 0; // Variable contenant la valeur de la tramme provenant du DSK
int trameEnvoyeDSK = 0xAA; // Variable contenant la valeur de la tramme envoye au DSK

 void main(void)
 {
     unsigned char status = 0;
     unsigned char data[5];
     int i;
 
     // run internal oscillator at 8 MHz

     
     initialisation_SPI();
     initialisation_PORT();
     //OpenSPI(SPI_FOSC_16, MODE_00, SMPMID); //open SPI1
     
     //Configure la communication UART avec le DSK
     configPIC_DSK();

     
    while(readBusyFlag());
    clearDisplay();
    displayCtrl(1,1,0);
    putStringLCD("Hello world");
    while (1)
    {
        if(flag_nouvelleTrameDSK)
        {
            lectureTrameDSK();
            flag_nouvelleTrameDSK = 0;
        }
        else if (flag_ecrireTrameDSK)
        {
            ecrireDSK_UART(trameEnvoyeDSK);
            //flag_ecrireTrameDSK = 0;
        }
     }
 }
 
/* void interrupt myIsr(void)
{
     if(PIR1bits.RC1IF == 1) // Bit de flag indiquant que le buffer de reception UART est plein
     {
         flag_nouvelleTrameDSK = 1; 
     }
}*/
 
 