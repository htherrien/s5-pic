
#include <pic18f67j94.h>

#include "IO.h"


void InitialisationIO(void)
{
    //Configuration des inputs
    TRISGbits.TRISG3 = 1; //Initialise la pin SG3 du port E en input (SWITCH))
    TRISGbits.TRISG4 = 1; //Initialise la pin SG4 du port E en input (BOUTTON))
     
    ANCON2bits.ANSEL14 = 0; // La pin est une entree digital
    ANCON2bits.ANSEL15 = 0; // La pin est une entree digital
    
    
    //Configuration des outputs
    TRISCbits.TRISC6 = 0; //Initialise la pin SG3 du port E en output (DEL vert))
    TRISCbits.TRISC5 = 0; //Initialise la pin SG4 du port E en output (DEL rouge))
    TRISCbits.TRISC2 = 0; //Initialise la pin SG4 du port E en output (DEL orange))
     
    
    LATCbits.LATC6 = 0; // initialise a 0
    LATCbits.LATC5 = 0; // initialise a 0
    LATCbits.LATC2 = 0; // initialise a 0
    
    //PADCFG1 | 0x10;
}

void allumeLEDRVJ(int DELR, int DELV, int DELJ)
{
    //Allume les dels en fonction des entrees de la fonction
    //ATTENTION: Prend 1 ou 0 en entree
    LATCbits.LATC6 = DELV;      // État DEL Verte
    LATCbits.LATC5 = DELR;      // État DEL Rouge
    LATCbits.LATC2 = DELJ;      // État DEL Jaune
}
