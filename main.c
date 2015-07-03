/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */


#include <libpic30.h>      /* Used for _delay_ms function  - must be included 
                              after FCY has been defined (in system.h) */


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 30;            // M = 32
    CLKDIVbits.PLLPOST=0;   // N2 = 2
    CLKDIVbits.PLLPRE=1;    // N1 = 3
    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
    while(OSCCONbits.LOCK!=1) {};

    while(1)
    {
        LATBbits.LATB12 = 0;    // set pin as low
        // LATB = 0x00;
        __delay_ms(1000);
        LATBbits.LATB12 = 1;    // set pin high
        __delay_ms(1000);
    }
}