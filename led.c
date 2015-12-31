/*
 * File:   led.c
 * Author: Harry Callahan
 *
 * Created on 24 December 2015, 11:14
 */

#include "main.h"

//initialisations
int threshold =  512;

///////////////////////////////////////////////////////////////////////////////

void Led_Cycle_Start(void)
{
/*
 * Led_Cycle_Start
 * Initialises the Led's for cycling by setting up the output pin registers, and...
 * ... starting the timer. It also sets an initial output led, RED, ON. 
 */
    LedDigital_IO_Init();
    Timer1Init();
    
    LATFbits.LATF4 = 0; // red
    LATFbits.LATF5 = 0;
}

void LedDigital_IO_Init(void)
{
/*
 * LedDigital_IO_Init
 * Sets up the TRIS and ODCG registers for the appropriate pins to control the...
 * ... tri-colour led.
 */ 
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
/*
 Toggles the red led on/off
 */
    LATFbits.LATF4 = ~LATFbits.LATF4;
    LATFbits.LATF5 = ~LATFbits.LATF5;
}

void toggle_green(void)
{
/*
 Toggles the green led on/off
 */
    LATGbits.LATG8 = ~LATGbits.LATG8;
    LATGbits.LATG9 = ~LATGbits.LATG9;
}

void toggle_blue(void)
{
/*
 Toggles the blue led on/off
 */
    LATGbits.LATG6 = ~LATGbits.LATG6;
    LATGbits.LATG7 = ~LATGbits.LATG7;
}

void Timer1Init(void)
{
/*
 * Timer1Init
 * Sets up Timer1 with given period, clock prescaler, and sets the interrupts. 
 * Enables the timer.
 */
    PR1                 = 0xFFFF;   // Timer period
    T1CONbits.TCKPS     = 0b10;     // Clock prescale 
    IFS0bits.T1IF       = 0;        // Reset interrupt flag
    IEC0bits.T1IE       = 1;        // Turn on the timer 1 interrupt.
    IPC0bits.T1IP       = 5;        // 
    
    T1CONbits.TON       = 1;        // Turn on timer 1.
}

void Timer1period(int period)
{
/*
 * Timer1period
 * Sets a new value for the Timer1 period register.
 * 
 * This can be called at any point, and will change the count comparator for the timer no matter what point through the cycle the current count is.
 * If the current count is very close to the new period, the interrupt may trigger very quickly and cause issues. 
 * 
 * Task : rewrite so to reset counter whenever new period is set.
 */
    PR1                 = period;   // Set new period for timer
}


void Cycle_Flash(void)
{
/*
 * Cycle_Flash
 * 
 * Switches the led so the next in the cycle is on, and the current led switches off. 
 * The cycle rotates as RED -> GREEN - > BLUE
 */    
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
}

