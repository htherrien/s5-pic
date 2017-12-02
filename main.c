/**************************************************************************
Version 1.2
 
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
#include "crc8.h"
#include "accelerometre.h"
 
//Variables
#define trameEnvoyeDSK 0xAA // Variable contenant la valeur de la tramme envoye au DSK

 void main(void)
 {
     initialisation_SPI();
     initialisation_PORT();
     ComputeTableCRC8();
     
     //Configure la communication UART avec le DSK
     configPIC_DSK();

     
    while(readBusyFlag());
    clearDisplay();
    displayCtrl(1,1,0);
    putStringLCD("Hello world");
    while (1)
    {
        DonneeAccel donnee;
        uint8_t* tamponEnvoiPtr;
        
        lireAccel(&donnee);
        tamponEnvoiPtr = encoderAccel(&donnee);
        ecrireMessageUART(tamponEnvoiPtr);
    }
 }
 
 void interrupt myIsr(void)
{
     if(PIR1bits.RC1IF == 1) // Bit de flag indiquant que le buffer de reception UART est plein
     {
          lectureCharUART();
         //PIR1bits.RC1IF = 0;
     }
}
 
 