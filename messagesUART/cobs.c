/*******************************************************************************
 * Projet S5
 * @file    cobs.c
 * @author  Hugo Therrien, Marc-André Roireau
 * @date    29 november 2017
 * @version 0.1
 *
 * Implements the COBS packet encoding/decoding algorithm
 *
 ******************************************************************************/

#include "cobs.h"

size_t cobsEncode(const uint8_t *input, size_t length, uint8_t *output)
{
    size_t readIndex = 0;
    size_t writeIndex = 1;
    size_t codeIndex = 0;
    uint8_t code = 0x01;
  
    while(readIndex < length)
    {
        if(input[readIndex] == 0x00)
        {
            output[codeIndex] = code;
            code = 0x01; // Reset the code
            codeIndex = writeIndex++;
            readIndex++;
        }
        else
        {
            output[writeIndex++] = input[readIndex++];
            code++;
            /* Case where there is more than 256 nonzero bytes in a row */
            if(code == 0xFF)
            {
                output[codeIndex] = code;
                code = 0x01;
                codeIndex = writeIndex++;
            }
        }
    }
    output[codeIndex] = code;
    output[writeIndex] = 0x00; // Write terminating byte
    return writeIndex;
}

size_t cobsDecode(const uint8_t* input, size_t length, uint8_t* output)
{
    size_t readIndex = 0;
    size_t writeIndex = 0;
    size_t codeIndex;
    uint8_t code;

    while(readIndex < length)
    {
        code = input[readIndex];
        if(readIndex + code > length && code != 1)
        {
            return 0;
        }
        readIndex++;
        for(codeIndex = 1; codeIndex < code; codeIndex++)
        {
            output[writeIndex++] = input[readIndex++];
        }
        if(code != 0xFF && readIndex != length)
        {
            output[writeIndex++] = '\0';
        }
    }
    return writeIndex;
}

