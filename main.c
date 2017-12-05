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
#include "I2C.h"
#include "messagesUART/messagesUART.h"
 
//Variables
#define trameEnvoyeDSK 0xAA // Variable contenant la valeur de la tramme envoye au DSK

 void main(void)
 {
     initialisation_SPI();
     initialisation_PORT();
     I2CInitialisation();
     ComputeTableCRC8();
     
     //Configure la communication UART avec le DSK
     configPIC_DSK();
     
    while(readBusyFlag());
    clearDisplay();
    displayCtrl(1,1,0);
    putStringLCD("Hello world");
    
    
    while (1)
    {
        uint8_t buf[6];
        DonneeAccel donnee;
        uint8_t* tamponEnvoiPtr;
        MPUReadBytes(buf, capteurXregH, 6);
        
        donnee.x = ((uint16_t)buf[0] << 8) + buf[1];
        donnee.y = ((uint16_t)buf[2] << 8) + buf[3];
        donnee.z = ((uint16_t)buf[4] << 8) + buf[5];
        
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
 
 