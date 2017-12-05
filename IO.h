/* 
 * File:   IO.h
 * Author: jola2202
 *
 * Created on 5 décembre 2017, 01:35
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
 //function prototypes
 void InitialisationIO(void);
 void allumeLEDRVJ(int DELR, int DELV, int DELJ);
    
 //Variables
    
 //Defines
#define LED_ON 1
#define LED_OFF 0

#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

