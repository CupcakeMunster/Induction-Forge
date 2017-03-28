/*
 * File:   debounce.c
 * Author: john
 *
 * Created on March 20, 2017, 5:04 PM
 */

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

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "debounce.h"        /* variables/params used by system.c             */   

unsigned int InputA (unsigned int input)
{
    /* These are the variables used */
    unsigned int static integrator;  /* Will range from 0 to the specified MAXIMUM */
    unsigned int static output;      /* Cleaned-up version of the input signal */

    /* Step 1: Update the integrator based on the input signal.  Note that the
    integrator follows the input, decreasing or increasing towards the limits as
    determined by the input state (0 or 1). */

    if (input == 0)
    {
        if (integrator > 0)
            integrator--;
    }
    else if (integrator < MAXIMUM)
        integrator++;

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either

    0 or MAXIMUM. */

    if (integrator == 0)
        output = 0;
    else if (integrator >= MAXIMUM)
        {
        output = 1;
        integrator = MAXIMUM;  /* defensive code if integrator got corrupted */
        }
    
    return output;
}

unsigned int InputB (unsigned int input)
{
    /* These are the variables used */
    unsigned int static integrator;  /* Will range from 0 to the specified MAXIMUM */
    unsigned int static output;      /* Cleaned-up version of the input signal */

    /* Step 1: Update the integrator based on the input signal.  Note that the
    integrator follows the input, decreasing or increasing towards the limits as
    determined by the input state (0 or 1). */

    if (input == 0)
    {
        if (integrator > 0)
            integrator--;
    }
    else if (integrator < MAXIMUM)
        integrator++;

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either

    0 or MAXIMUM. */

    if (integrator == 0)
        output = 0;
    else if (integrator >= MAXIMUM)
        {
        output = 1;
        integrator = MAXIMUM;  /* defensive code if integrator got corrupted */
        }
    
    return output;
}