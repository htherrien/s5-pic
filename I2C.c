/*
 * File:   I2C.c
 * Author: Alexandre Joly
 *
 * Created on 29 novembre 2017, 14:59
 */



#include "I2C.h"
uint8_t I2CInitialisation(void)
{
    OpenI2C(MASTER, SLEW_OFF);
    uint8_t valeur;
    SSP1ADD = 19; // Set the Baud rate for a master use
    
    
    I2CWriteSeq(CapteurPwrreg,0x08);
    I2CWriteSeq(CapteurAccelConfig,0x18);
    I2CWriteSeq(CapteurAccelConfig,0x18);
    
   valeur=WHOAMI();
   
   return valeur;

}

void InitialisationIntI2C(void)
{
    // Initialise l'interuption qui indicte au compilateur qu'il faut faire une lecture I2C
    
    // Initialisation de l'horloge Timer0 
    TMR0L = 0xFF;		//chargement du compte LSB
    TMR0H = 0xFF;		//chargement du compte MSB
    T0CON = 0xD1;         //PRESCALER VALUE: Sert � initialiser la fr�quence d'�chantillonnage 
    T0CONbits.TMR0ON=1;    // mise en route de l'horloge

    // initialisation des interruptions
    INTCONbits.TMR0IF = 0; // Descend le flag TMR0
    INTCONbits.TMR0IE = 1; // Enable 
    INTCONbits.GIE = 1;
    PIE2bits.BCL1IE = 1;
    //RCON = RCON | 0x80;
    
}
uint8_t WHOAMI(void)
{



    //Variables
    uint8_t donnee_x1;
    uint8_t cmd_byte, status, addr;
    
    
    //START CONDITION
    StartI2C();
    
      do{
        
       WriteI2C(CapteurWriteAddress);
    
     }while(SSP1CON2bits.ACKSTAT);
    
    
    //Wait for acknowledge from slave
    do{
        
        WriteI2C(capteurWhoAmIreg);
    
     }while(SSP1CON2bits.ACKSTAT);
    
    
    //START CONDITION
    StartI2C();
    
 
    //Wait for acknowledge from slave
    do{
    WriteI2C(CapteurReadAddress);
    }while(SSP1CON2bits.ACKSTAT);
    
    
    //Read data from slave
    donnee_x1 = getcI2C();

    //Not acknowledge from master
    NotAckI2C1();
    
    //Stop condition
    StopI2C();
    
    return donnee_x1;
}

uint8_t I2CsingleRead(uint8_t rega)
{

    //Variables
    uint8_t donnee_x1;
     
    //START CONDITION
    StartI2C();
    
    //Address in writing mode
    WriteI2C(CapteurWriteAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT); //Bit 6 (I2C_V4 routine does not ackn.
    
    // Address register to read
    WriteI2C(rega);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    
    //START CONDITION
    StartI2C();
    
    //Address of slave in read mode
    WriteI2C(CapteurReadAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    
    //Read data from slave
    donnee_x1 = getcI2C();

    //Not acknowledge from master
    NotAckI2C1();
    
    //Stop condition
    StopI2C();
    
    return donnee_x1;
}

void MPUReadBytes(uint8_t buffer[], uint8_t registre, int taille)
{
    int i = 0;
    // Start condition
    StartI2C();
    
    //Address in writing mode
    WriteI2C(CapteurWriteAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT); //Bit 6 (I2C_V4 routine does not ackn.
    
    // Address register to read 
    WriteI2C(registre);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    //IdleI2C();
    
    //START CONDITION
    StartI2C();
    
    //Address of slave in read mode
    WriteI2C(CapteurReadAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    
    /* Read loop */
    for(i = 0; i < taille - 1; i++)
    {
        buffer[i] = getcI2C();
        AckI2C();
    }
    
    buffer[i] = getcI2C();
    //Acknowledge from master
    NotAckI2C1();

    //Stop condition
    StopI2C();
}


int I2CReadSeq(void)
{
    
    //Variables
    uint8_t donnee_x1,donnee_x2;
    int16_t  donnee_x;
    
    
    //START CONDITION
    StartI2C();
    
    //Address in writing mode
    WriteI2C(CapteurWriteAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT); //Bit 6 (I2C_V4 routine does not ackn.
    
    // Address register to read 
    WriteI2C(capteurXregH);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    //IdleI2C();
    
    //START CONDITION
    StartI2C();
    
    //Address of slave in read mode
    WriteI2C(CapteurReadAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    //IdleI2C();
    
    //Read data from slave
    donnee_x1 = getcI2C();
    //IdleI2C();
    
    //Acknowledge from master
    AckI2C();
    
    donnee_x2 = getcI2C();
    
    //Acknowledge from master
    NotAckI2C1();

    
    //Stop condition
    StopI2C();
    
    donnee_x = ((uint16_t) donnee_x1 << 8) + donnee_x2;
    return donnee_x;
}

int I2CWriteSeq(char reg,char config)
{
    
 
    //START CONDITION
    StartI2C();
    
    //Address in writing mode
    WriteI2C(CapteurWriteAddress);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT); //Bit 6 (I2C_V4 routine does not ackn.
    
    // Address register to read 
    WriteI2C(reg);
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    //IdleI2C();
    
    
    //Address of slave in read mode
    WriteI2C(config);  //disable sleep
    
    //Wait for acknowledge from slave
    while(SSP1CON2bits.ACKSTAT);
    
    //Stop condition
    StopI2C();
    
    return 0;
}
