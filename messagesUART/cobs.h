/*******************************************************************************
 * Projet S5
 * @file    cobs.h
 * @author  Hugo Therrien, Marc-André Roireau
 * @date    29 november 2017
 * @version 0.1
 *
 * Declares the cobs algorithm prototypes
 *
 ******************************************************************************/

#ifndef COBS_H
#define COBS_H

#include <stdint.h>
#include <stddef.h>

#define COBS_OVERHEAD 2

/*
 * @brief Encodes a string using the cobs encoding algorithm.
 *        The output is of size length + 1, excluding the
 *        terminating '\0'
 * @param[in] input the input string to be encoded
 * @param[in] length of the input string
 * @param[out] output the string resulting of the encoding of input 
 */
size_t cobsEncode(const uint8_t *input, size_t length, uint8_t *output);

/*
 * @brief Decodes a string using the cobs decoding algorithm.
 *        The output is supposed to be of size length - 1,
 *        excluding the terminating '\0'
 * @param[in] input the input string to be decoded
 * @param[in] length the size of the input string
 * @param[out] output the decoded string.
 */
size_t cobsDecode(const uint8_t* input, size_t length, uint8_t* output);

#endif
