/**************************************************************************
Version 1.0
 
Auteur : Hugo Daniel, Cedrik Maillette
Date de création : 29/11/2017
 
Liste de modification:
1. Modifé par: NAME LASTNAME
 
Description : Header file en rapport avec la communication PIC DSK
Propriété : Les S de Sherbrooke
**************************************************************************/


#ifndef COMMPIC_DSK_H
#define	COMMPIC_DSK_H

#include <p18f67j94.h>
#include "stdint.h"
#include "messagesUART.h"

 //function prototypes
void configPIC_DSK(void);
void configUART(void);
void configIntUART(void);
unsigned char lectureCharUART(void);
void ecrireCharUART(unsigned char trameEnvoye_DSK);
int ecrireMessageUART(uint8_t message[]);
uint8_t* encoderAccel(DonneeAccel* donnee);

 // Defines
#define BAUDRATE 16 //Voir section 21: http://ww1.microchip.com/downloads/en/DeviceDoc/30000575C.pdf

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* COMMPIC_DSK_H */

