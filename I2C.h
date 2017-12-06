
#ifndef I2C_H
#define	I2C_H

#include <p18f67j94.h>
#include <xc.h>
#include <plib/i2c.h>
#include <stdint.h>
#include <stdio.h>
 //function prototypes
  uint8_t I2CInitialisation(void);
  void InitialisationIntI2C(void);
  int I2CReadSeq(void);
  uint8_t WHOAMI(void);
  void MPUReadBytes(uint8_t buffer[], uint8_t registre, int taille);
  uint8_t I2CsingleRead(char rega);
  int I2CWriteSeq(char reg,char config);
 // Defines
 #define capteurXregH   59        // High bytes register address accel x MPU6050
 #define capteurXregL   60        // Low bytes register address accel x MPU6050
 #define capteurWhoAmIreg 117       //Who am I function address register
 #define CapteurWriteAddress 0xD0 //Slave address writing mode
 #define CapteurReadAddress 0xD1 //Slave address Reading mode
 #define CapteurPwrreg 107
 #define CapteurAccelConfig 28

 
#define _XTAL_FREQ 8000000

 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* I2C_H*/