/**************************************************************************
Version 1.
 
Auteur : Hugo Therrien
Date de création : 12/2017
 
Description : Fichier de décodage et d'encodage des messages
Propriété Les S de Sherbrooke
**************************************************************************/

#include "messagesUART.h"
#include "cobs.h"
#include "crc8.h"
#include "assert.h"

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

uint8_t* encoderAccelCRC(DonneeAccelCRC* donnee)
{
    donnee->header = MESSAGE_ACCEL_CRC;
    donnee->crc8 = ComputeCRC8((uint8_t*) donnee, TAILLE_MESSAGE_ACCEL);
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL_CRC, tamponEnvoi);
    return tamponEnvoi;
}

void decoderMessage(uint8_t* message, uint8_t taille)
{
    uint8_t header;
    assert(taille < TAILLE_TAMPON_RECEPTION);
    cobsDecode(message, taille, tamponReception);
    header = tamponReception[0];

    switch(header)
    {
        case MESSAGE_ACCEL:
        {
            DonneeAccel* accelDecode;
            accelDecode = (DonneeAccel*)(&tamponReception[1]);
            // appeler la fonction appropriée
            break;
        }
        default:
            break;
    }
}
