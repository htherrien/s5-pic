/**************************************************************************
Version 1.
 
Auteur : Hugo Therrien
Date de création : 12/2017
 
Description : Fichier de décodage et d'encodage des messages
Propriété Les S de Sherbrooke
**************************************************************************/

#include "accelerometre.h"
#include "cobs.h"

#define TAILLE_TAMPON_ENVOI 32
#define TAILLE_TAMPON_RECEPTION TAILLE_TAMPON_ENVOI
#define TAILLE_MESSAGE_ACCEL (sizeof(DonneeAccel))
#define TAILLE_MESSAGE_ACCEL_CRC (sizeof(DonneeAccel) + 1)

static uint8_t tamponEnvoi[TAILLE_TAMPON_ENVOI] = {0};
static uint8_t tamponReception[TAILLE_TAMPON_RECEPTION] = {0};

uint8_t* encoderAccel(DonneeAccel* donnee)
{   
    donnee->header = MESSAGE_ACCEL;
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL, tamponEnvoi);
    return tamponEnvoi;
}

void decoderMessage(uint8_t* message)
{
    uint8_t header = message[1];
    switch(header)
    {
        case MESSAGE_ACCEL:
            DonneeAccel* accelDecode;
            cobsDecode(message, TAILLE_MESSAGE_ACCEL + COBS_OVERHEAD, tamponReception);
            accelDecode = (DonneeAccel*)(&tamponReception[1]);
            // appeler la fonction appropriée
            break;
        default:
            break;
    }
}
