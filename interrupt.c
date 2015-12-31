/*
 * File:   interrupt.c
 * Author: Harry
 *
 * Created on 31 December 2015, 08:33
 */

#include "main.h"

int counter1 = 0;
int counter2 = 0;

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void) 
{
/*
 * _T1Interrupt
 * Primary interrupt vector name for PIC24F for "TMR1 Timer 1 expired"
 * 
 * To reduce latency, ISR should avoid calling any functions. Any processing should take place in the main() function. 
 * The ISR can interact with the main() processing using global variables, for example. 
 * These can then be operated on within the main loop, using atomic operations where necessary. 
 * If necessary, interrupts can be disabled while these operations are run. To see how..
 * .. see "XC16 C Compiler User Guide, pg. 220" for a starting example.
 */
   
    ReadPotentiometer();
    
    Timer1period(adc_pot*63);
    
    Cycle_Flash();
    
    counter1++; //debug
            
    IFS0bits.T1IF       = 0;        // Always clear interrupt flag before exit of ISR
}