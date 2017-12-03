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
    
typedef struct DonneeAccel
{
    uint8_t header;
    uint16_t x;
    uint16_t y;
    uint16_t z;
}DonneeAccel;
    
uint8_t* encoderAccel(DonneeAccel* donnee);

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGESUART_H */

