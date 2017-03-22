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

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    /* PWM Output pin control assigned to PWM generator */
    IOCON1bits.PENH = 1;
    IOCON1bits.PENL = 1;
    /* High and Low switches set to active-high state */
    IOCON1bits.POLH = 0;
    IOCON1bits.POLL = 0;
    
    /* Setup for the PWM clock to use the FRC as the REFCLK */
    /* ((FRC * 16) / APSTSCLR) = (7.37 * 16) / 1 = 117.9 MHz */
    ACLKCONbits.FRCSEL = 1;         /* FRC is input to Auxiliary PLL */
    ACLKCONbits.SELACLK = 1;        /* Auxiliary Oscillator provides the clock source */
    ACLKCONbits.APSTSCLR = 7;       /* Divide Auxiliary clock by 1 */
    ACLKCONbits.ENAPLL = 1;         /* Enable Auxiliary PLL */
    while(ACLKCONbits.APLLCK != 1); /* Wait for Auxiliary PLL to Lock */

    PWMCON1bits.CAM = 0; // For Edge-Aligned Mode
    PTCON2bits.PCLKDIV = 0; // Secect 1:2 PWM input time base (2.08nS resolution)
    PWMCON1bits.ITB = 0; // PTPER provides the PWM time period value
    PTPER = 12000;

    PWMCON1bits.MDCS = 0; // PDC1 provides duty cycle value
    PDC1 = 6000;    // Independent Primary Duty Cycle is 50% of the period
    SDC1 = 2404;    // Independent Secondary Duty Cycle is 50% of the period
    MDC = 2404;     // Master Duty Cycle is 50% of the period

    IOCON1bits.PMOD = 0; // For Complementary Output mode
    
    /* Enable High-Speed PWM module */
    PTCONbits.PTEN = 1;

}
