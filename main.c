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
#include "IO.h"
 
//Defines
//#define trameEnvoyeDSK 0xAA // Variable contenant la valeur de la tramme envoye au DSK

//Variables globale
//char ValeurReussi = 0x69; // Valeur qui indique q'une correlation a ete reussite
int readI2C_flag = 0; // Flag qui indique de commencer une lecture I2C
int resultat_corr = 0;
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
	moveCursor(1,2);
    putStringLCD("Bonjour");
    InitialisationIO();         // Initialisation I/O PORTs
    
    while (1)
    {    
        if(PORTGbits.RG4==1)    //switch fermꥍ
        {
             if(pauseFlag == 1)
             {
            while(readBusyFlag());
            clearDisplay();
            moveCursor(1,2);
            putStringLCD("Pause");     // LCD affiche le mode pause
             }
            pauseFlag = 0;
            modeCurseurAffichage = 0;
            modeCorrelationAffichage = 0;
            LATCbits.LATC6 = 0;  //Close LED Verte
            LATCbits.LATC5 = 0;  //Close LED Rouge
            LATCbits.LATC2 = 0;  //Close LED jaune
        } 
        else
        {
            pauseFlag = 1;
            LATCbits.LATC6 = 1;  //Open LED Verte
        
        //SECTION COMMUNICATION OUTPUT DSK
            if(PORTGbits.RG3==0)     //bouton
            {
                if(modeCorrelationAffichage == 0)
                {
                    modeCorrelationAffichage = 1;
                    while(readBusyFlag());
                    clearDisplay();
                    putStringLCD("Mode Correlation");   // LCD affiche le mode
                    
/************************************************************/   
/*                    AFFICHAGE RʓULTAT                    */                                       
/************************************************************/ 
                   if(resultat_corr < 90 || resultat_corr > 100)
                   {
                      
                      moveCursor(1,1);
                      putStringLCD("similarite:");
                      moveCursor(1,13);
                      if(resultat_corr < 1 || resultat_corr > 100)
                      {
                        putStringLCD("0%");  
                      }
                      else
                      {
                      putNumberLCD(resultat_corr);
                      putStringLCD("%");
                      }
                      moveCursor(2,1);
                      clearRow(2);
                      putStringLCD("Mouvement inconnu");  
                      
                   }
                   else 
                   {
                      moveCursor(1,1);
                      putStringLCD("similarite:");
                      moveCursor(1,13);
                      putNumberLCD(resultat_corr);
                      putStringLCD("%");
                      moveCursor(2,1);
                      clearRow(2);
                      putStringLCD("Mouvement reussi");  
                   }
/************************************************************/   
/*                 FIN AFFICHAGE RʓULTAT                   */                                       
/************************************************************/ 
                    
                }
                modeCorrelation = 1;                // Mode Correlation activ鍊
                modeCurseurAffichage = 0;
                //SECTION COMMUNICATION INPUT DSK
                LATCbits.LATC5 = 0;  //Close LED Rouge
                LATCbits.LATC2 = 1;  //Open LED jaune
                trameRecue_DSK = 0;  //Pr봠pour une autre trame
            }  
            if(PORTGbits.RG3==1)     //bouton
            {
                if(modeCurseurAffichage == 0)
                {
                    while(readBusyFlag());
                    clearDisplay();
                    moveCursor(1,2);
                    putStringLCD("Mode Curseur");   // LCD affiche le mode
                    modeCurseurAffichage = 1;
                }
                modeCorrelationAffichage = 0;
                modeCorrelation = 0;            // Mode Curseur activ鍊
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
		 resultat_corr = trameRecue_DSK;
         donneeDSK_ready = 1; // Donnee du DSK lue
     }
     
     if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) 
     { 
        INTCONbits.TMR0IF = 0; // remise � zero du flag interne d'interruption
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

