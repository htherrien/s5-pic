/*******************************************************************************
 * Projet S5 - copyright Bastian Molkenthin
 * @see     http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch44
 * @file    crc8.c
 * @author  Hugo Therrien, Marc-André Roireau
 * @date    29 november 2017
 * @version 0.1
 *
 * Implements CRC8
 *
 ******************************************************************************/

#include "crc8.h"

static uint8_t crctable[256];

void ComputeTableCRC8(void)
{
    const uint8_t generator = 0x1D;
    uint16_t divident;
    /* iterate over all byte values 0 - 255 */
    for (divident = 0; divident < 256; divident++)
    {
        uint8_t bitIterator;
        uint8_t currByte = (uint8_t)divident;
        /* calculate the CRC-8 value for current byte */
        for (bitIterator = 0; bitIterator < 8; bitIterator++)
        {
            if ((currByte & 0x80) != 0)
            {
                currByte <<= 1;
                currByte ^= generator;
            }
            else
            {
                currByte <<= 1;
            }
        }
        /* store CRC value in lookup table */
        crctable[divident] = currByte;
    }
}

uint8_t ComputeCRC8(uint8_t bytes[], size_t length)
{
    size_t index;
    uint8_t crc = 0;
    for(index = 0; index < length; index++)
    {
        /* XOR-in next input byte and
         * get current CRC value = remainder */
        crc = crctable[bytes[index] ^ crc];
    }
    return crc;
}
