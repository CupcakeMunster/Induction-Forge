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
#include "debounce.h"      /* User functions for software input debouncing    */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{   
    unsigned int inputAlatch, inputBlatch; 
    
    Nop();
    Nop();
    RCON = 0;
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {
        // Check RB0 input and increment PTPER
        if (InputA(PORTAbits.RA0) == 1) 
            // Only action the input on a new press
            while (inputAlatch != 1)    
            {
                PTPER = PTPER + 10;
                PDC1 = PTPER / 2;
                inputAlatch = 1;
            }
        // Otherwise clear the input latch
        else
            inputAlatch = 0;
        
        // Check RB1 input and decrement PTPER
        if (InputB(PORTAbits.RA1) == 1)
            // Only action the input on a new press
            while (inputBlatch != 1)
            {
                PTPER = PTPER - 10;
                PDC1 = PTPER / 2;                
                inputBlatch = 1;
            }
        // Otherwise clear the input latch
        else
            inputBlatch = 0;
    }
}
