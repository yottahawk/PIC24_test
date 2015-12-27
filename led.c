/*
 * File:   led.c
 * Author: Harry Callahan
 *
 * Created on 24 December 2015, 11:14
 */

#include "main.h"

//initialisations
int counter1 = 0;

void Led_Cycle(void)
{
    LedDigital_IO_Init();
    Timer1Init();
    
    LATGbits.LATG8 = 1; // start cycle with different bit
    LATGbits.LATG9 = 1;
}

void LedDigital_IO_Init(void)
{
    AD1PCFGL    = 0xFFFF;    // Set analog function pins used for LED's to digital I/O
    
    TRISG       = 0xFC3F;    // Set band G led pins to output
    ODCG        = 0x03C0;    // Set green and blue led to open drain. (Schematic requires these pins to sink current for operation of LED's)
    
    TRISF       = 0x00CF;    // Set bank F led pins to output
    ODCF        = 0x0030;    // Set red led pins to open drain.       (Schematic requires these pins to sink current for operation of LED's)
    
    // Initialise outputs to 1 -> turns LED's off.
    LATGbits.LATG6 = 1; // blue
    LATGbits.LATG7 = 1;
    
    LATGbits.LATG8 = 1; // green
    LATGbits.LATG9 = 1;
    
    LATFbits.LATF4 = 1; // red
    LATFbits.LATF5 = 1;
}


void toggle_red(void)
{
    LATFbits.LATF4 = ~LATFbits.LATF4;
    LATFbits.LATF5 = ~LATFbits.LATF5;
}

void toggle_green(void)
{
    LATGbits.LATG8 = ~LATGbits.LATG8;
    LATGbits.LATG9 = ~LATGbits.LATG9;
}

void toggle_blue(void)
{
    LATGbits.LATG6 = ~LATGbits.LATG6;
    LATGbits.LATG7 = ~LATGbits.LATG7;
}

void Timer1Init(void)
{
    PR1                 = 0xFFFF;   // Timer period
    T1CONbits.TON       = 1;        // Turn on timer 1.
    T1CONbits.TCKPS     = 0b11;     // Clock prescale 
    IFS0bits.T1IF       = 0;        // Reset interrupt flag
    IEC0bits.T1IE       = 1;        // Turn on the timer 1 interrupt.
    IPC0bits.T1IP       = 5;        // 
}

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void) // uses ISR macro
{
    /*  */
    
    if (LATFbits.LATF4 == 0) // if red on
    {
        toggle_red();
        toggle_green();
    }
    else if (LATGbits.LATG8 == 0) // if green on
    {
        toggle_green();
        toggle_blue();
    }
    else if (LATGbits.LATG6 == 0) // if blue on
    {
        toggle_blue();
        toggle_red();
    } 
    
    counter1++; //debug
            
    IFS0bits.T1IF       = 0;        // Always clear interrupt flag before exit of ISR
}