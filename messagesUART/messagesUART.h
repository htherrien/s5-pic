/* 
 * File:   messagesUART.h
 * Author: danh2801
 *
 * Created on 2 décembre 2017, 17:42
 */

#ifndef MESSAGESUART_H
#define	MESSAGESUART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MESSAGE_ACCEL 0x01
#define MESSAGE_ACCEL_CRC 0x81

#include <stdint.h>

#define TAILLE_EXTRA_COBS_ENCODE 1
#define TAILLE_EXTRA_COBS_DECODE 2

typedef struct DonneeAccel
{
    int16_t header;
    int16_t x;
    int16_t y;
    int16_t z;
}DonneeAccel;
#define TAILLE_MESSAGE_ACCEL sizeof(DonneeAccel)

typedef struct DonneeAccelCRC
{
    int16_t header;
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t crc8;
}DonneeAccelCRC;

#define TAILLE_MESSAGE_ACCEL_CRC sizeof(DonneeAccelCRC)
    
uint8_t* encoderAccel(DonneeAccel* donnee);

/*
 * Retourne !NULL si typeDécodé == typeAttendu
 */
void* decoderMessage(uint8_t* message, uint8_t taille, const uint8_t typeAttendu);

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGESUART_H */

