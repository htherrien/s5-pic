/* 
 * File:   accelerometre.h
 * Author: danh2801
 *
 * Created on 2 décembre 2017, 16:58
 */

#ifndef ACCELEROMETRE_H
#define	ACCELEROMETRE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "messagesUART.h"

void lireAccel(DonneeAccel* donnee);

#ifdef	__cplusplus
}
#endif

#endif	/* ACCELEROMETRE_H */

