/**************************************************************************
Version 1.2
 
Auteur : Danae Dufour-Forget, Franck Laouhap
Date de crÃ©ation : 10/2017
 
Liste de modification:
1. ModifÃ© par: Hugo Daniel et Cedrik Maillette  Date: 29/11/2017
 
Description : Fichier main pour le PIC
PropriÃ©tÃ© : Les S de Sherbrooke
**************************************************************************/

// Librairies
#include "LCD_SPI.h"
#include "commPIC_DSK.h"
#include "I2C.h"
#include "messagesUART/messagesUART.h"
#include "IO.h"
 
//Defines
#define trameEnvoyeDSK 0xAA // Variable contenant la valeur de la tramme envoye au DSK
int test = 0;

//Variables globale
char ValeurReussi = 0x69; // Valeur qui indique q'une correlation a ete reussite
int readI2C_flag = 0; // Flag qui indique de commencer une lecture I2C
int donneeDSK_ready = 0; // Flag indiquant qu'une donnee venant du DSK a ete lue
unsigned char trameRecue_DSK = 0; // Trame recue du DSK;
int modeCorrelation = 0;    // Active le mode Correlation
int modeCorrelationAffichage = 0;    // Active l'affichage pour la correlation
int modeCurseurAffichage = 0;        // Active l'affichage pour la curseur
int pauseFlag = 0;    // Active l'affichage
int reussi=0;

 void main(void)
 {
     //Fonctions d'initialisation
     initialisation_SPI();      // Initialisation SPI
     initialisation_PORT();     // Initialisation PORTs
     reussi=I2CInitialisation();       // Initialisation I2C
     ComputeTableCRC8();
     InitialisationIntI2C();    // Initialisation interrup I2C
     configPIC_DSK();           // configuration UART

     
    while(readBusyFlag());
    clearDisplay();
    displayCtrl(1,1,0);
    putStringLCD("Bonjour");
    InitialisationIO();         // Initialisation I/O PORTs
    
    while (1)
    {    
        if(PORTGbits.RG4==1)    //switch fermée
        {
            if(pauseFlag == 0)
            {
               while(readBusyFlag());
               clearDisplay();
               putStringLCD("Pause");     // LCD affiche le mode pause
            }
            pauseFlag = 1;
            modeCorrelationAffichage = 0;          // Affichage du mode Correlation
            modeCurseurAffichage = 0;              // Affichage du mode Curseur
            LATCbits.LATC6 = 0;  //Close LED Verte
            LATCbits.LATC5 = 0;  //Close LED Rouge
            LATCbits.LATC2 = 0;  //Close LED jaune
        } 
        else
        {
            
            pauseFlag = 0;
            LATCbits.LATC6 = 1;  //Open LED Verte
            
            //SECTION COMMUNICATION INPUT DSK
            if(donneeDSK_ready)
            {
                if(ValeurReussi == trameRecue_DSK && modeCorrelation == 1)
                {
                    LATCbits.LATC5 = 0;  //Close LED Rouge
                    LATCbits.LATC2 = 1;  //Open LED jaune
                    trameRecue_DSK = 0;  //Prêt pour une autre trame
                }
            }
        
        //SECTION COMMUNICATION OUTPUT DSK
            if(PORTGbits.RG3==0)     //bouton
            {
                if(modeCorrelationAffichage == 0)
                {
                    while(readBusyFlag());
                    clearDisplay();
                    putStringLCD("Mode Correlation");   // LCD affiche le mode
                }
                modeCorrelation = 1;                // Mode Correlation activé
                modeCorrelationAffichage = 1;       // Afficher le mode Correlation
                modeCurseurAffichage = 0;           // Afficher le mode Curseur
            }  
            if(PORTGbits.RG3==1)     //bouton
            {
                if(modeCurseurAffichage == 0)
                {
                    while(readBusyFlag());
                    clearDisplay();
                    putStringLCD("Mode Curseur");   // LCD affiche le mode
                }
                modeCorrelation = 0;            // Mode Curseur activé
                modeCurseurAffichage = 1;       // Afficher le mode Curseur
                modeCorrelationAffichage = 0;   // Afficher le mode Correlation
                LATCbits.LATC5 = 1;  //Open LED Rouge
                LATCbits.LATC2 = 0;  //Close LED jaune
            }  
               
            //SECTION LECTURE MPU6050
            if(readI2C_flag)
            {
                uint8_t buf[6];
                DonneeAccel donnee;
                uint8_t* tamponEnvoiPtr;
                MPUReadBytes(buf, capteurXregH, 6);

                donnee.x = ((uint16_t)buf[0] << 8) + buf[1];
                donnee.y = ((uint16_t)buf[2] << 8) + buf[3];
                donnee.z = ((uint16_t)buf[4] << 8) + buf[5];
                if(modeCorrelation)
                {
                    donnee.mode = MODE_CORRELATION;
                }
                else
                {
                    donnee.mode = MODE_SOURIS;
                }

                tamponEnvoiPtr = encoderAccel(&donnee);
                ecrireMessageUART(tamponEnvoiPtr);
                readI2C_flag=0;
            } 
        }
    }
}
         

 
 void interrupt low_priority myIsr(void)
{
     if(PIR2bits.BCL1IF == 1)   {
            while(readBusyFlag());
           clearDisplay();
           putStringLCD("BUGGE");   // LCD affiche le mode
           while(1){AckI2C();}
        }
     if(PIR1bits.RC1IF == 1) // Bit de flag indiquant que le buffer de reception UART est plein
     {
         trameRecue_DSK = lectureCharUART();
         donneeDSK_ready = 1; // Donnee du DSK lue
     }
     
     if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) 
     { 
        INTCONbits.TMR0IF = 0; // remise à zero du flag interne d'interruption
        readI2C_flag = 1; // On leve le flag readI2C_flag pour que les donnees I2C soient lue dans le main
     }
     
}
 
 /*void interrupt high_priority isr(void)
 {
    if(PIR2bits.BCL1IF == 1)   {
            while(readBusyFlag());
           clearDisplay();
           putStringLCD("BUGGE");   // LCD affiche le mode
           while(1){}
        }
 }*/

