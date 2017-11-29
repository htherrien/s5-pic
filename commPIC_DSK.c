
#include "commPIC_DSK.h"



void configPIC_DSK(void)
{
    
}

void portUART(void)
{
    // configuration des pins
    TRISDbits.TRISD6 = 0; //TX set output
    TRISDbits.TRISD7 = 1; //RX set input
    
    // configuration communication
    SPBRG = BAUDRATE; // set baud rate pour 
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
    BAUDCONbits.BRG16 = 1;
    
    
    
}

