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

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{
    /* Setup an oscillator reference on RP1 pin*/
    RPOR0 = 38;
    REFOCON = 0x8000;
    
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 41;            // M = 43
    CLKDIVbits.PLLPOST=0;   // N2 = 2
    CLKDIVbits.PLLPRE=0;    // N1 = 2
    Nop();
    
    /* Disable the watchdog timer */
    RCONbits.SWDTEN = 0;
    
    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);

    while (OSCCONbits.COSC != 0b001);   // Wait for Clock switch to occur
    while (OSCCONbits.LOCK!=1);         // Wait for PLL to lock
}
#if 0
        /* Disable Watch Dog Timer */
        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Primary Osc (HS, XT, EC) */
        __builtin_write_OSCCONH(0x02);  /* Set OSCCONH for clock switch */
        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, only if PLL is needed */
        /* while(OSCCONbits.LOCK != 1); */
#endif
        
void InitApp (void)
{
    /**************************************************************************/
    /* Port initialization                                                    */
    /**************************************************************************/
    ADPCFG = 0xFFFF;    // All digital pins
    
    TRISA = 3;          // Set RA0 - RA1 as inputs
    LATA = 0;           // Set Port A low
    TRISB = 0;          // Set Port B as outputs
    LATB = 0;           // Set Port B low
    /**************************************************************************/
    /* PWM initialization                                                     */
    /**************************************************************************/
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

    PWMCON1bits.CAM = 0;    // For Edge-Aligned Mode
    PTCON2bits.PCLKDIV = 0; // Select 1:2 PWM input time base (2.08nS resolution)
    PWMCON1bits.ITB = 0;    // PTPER provides the PWM time period value
    PTPER = 12000;

    PWMCON1bits.MDCS = 0;   // PDC1 provides duty cycle value
    PDC1 = 6000;            // Independent Primary Duty Cycle is 50% of the period
    SDC1 = 1000;            // Independent Secondary Duty Cycle is 50% of the period
    MDC = 1000;             // Master Duty Cycle is 50% of the period

    IOCON1bits.PMOD = 0;    // For Complementary Output mode
    
    /* Select Dead Time control */
    PWMCON1bits.DTC = 0;    // Positive Dead Time applied for all modes
    DTR1 = 65;              // Dead Time value is 65.5 ns
    ALTDTR1 = 65;           // Alternate Dead time value is 65.5 ns
    
    /* Enable High-Speed PWM module */
    PTCONbits.PTEN = 1;

    /**************************************************************************/
    /* UART initialization                                                    */
    /**************************************************************************/
    
    /**************************************************************************/
    /* I2C initialization                                                     */
    /**************************************************************************/
}

