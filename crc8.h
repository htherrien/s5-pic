/*******************************************************************************
 * Projet S5
 * @file    crc8.h
 * @author  Hugo Therrien, Marc-André Roireau
 * @date    29 november 2017
 * @version 0.1
 *
 * Declares the functions used for CRC8
 *
 ******************************************************************************/

#ifndef CRC8_H
#define CRC8_H

#include <stdint.h>
#include <stddef.h>

void ComputeTableCRC8(void);

uint8_t ComputeCRC8(uint8_t bytes[], size_t length);

#endif
