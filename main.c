#include "LCD_SPI.h"
 

 void main(void)
 {
     unsigned char status = 0;
     unsigned char data[5];
     int i;
 
     // run internal oscillator at 8 MHz

     
     initialisation_SPI();
     initialisation_PORT();
     //OpenSPI(SPI_FOSC_16, MODE_00, SMPMID); //open SPI1
     

     
    while(readBusyFlag());
    clearDisplay();
    displayCtrl(1,1,0);
    putStringLCD("Hello world");
     while (1)
     {
        
     }
 }
 
 