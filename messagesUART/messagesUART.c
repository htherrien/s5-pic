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

#define TAILLE_TAMPON_ENCODAGE 32
#define TAILLE_TAMPON_DECODAGE TAILLE_TAMPON_ENCODAGE

static uint8_t tamponEncodage[TAILLE_TAMPON_ENCODAGE] = {0};
static uint8_t tamponDecodage[TAILLE_TAMPON_DECODAGE] = {0};

uint8_t* encoderAccel(DonneeAccel* donnee)
{   
    donnee->header = MESSAGE_ACCEL;
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL + TAILLE_EXTRA_COBS_ENCODE, tamponEncodage);
    return tamponEncodage;
}

uint8_t* encoderAccelCRC(DonneeAccelCRC* donnee)
{
    donnee->header = MESSAGE_ACCEL_CRC;
    donnee->crc8 = ComputeCRC8((uint8_t*) donnee, TAILLE_MESSAGE_ACCEL + 1);
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL_CRC + TAILLE_EXTRA_COBS_ENCODE, tamponEncodage);
    return tamponEncodage;
}

void decoderMessage(uint8_t* message, uint8_t taille)
{
    uint8_t header;
    assert(taille < TAILLE_TAMPON_DECODAGE);
    cobsDecode(message, taille, tamponDecodage);
    header = tamponDecodage[0];

    switch(header)
    {
        case MESSAGE_ACCEL:
        {
            DonneeAccel* accelDecode;
            accelDecode = (DonneeAccel*)(&tamponDecodage[0]);
            // appeler la fonction appropriée
            break;
        }
        default:
            break;
    }
}
