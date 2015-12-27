/* 
 * File: main.c   
 * Author: Harry Callahan
 * Comments: A test project for experimenting with programming of the PIC24FJ256GB106 in the starter kit.
 * Revision history: 
 */

//Function prototypes

void Led_Cycle(void); // Start cyclical flashing of LED's.

void LedDigital_IO_Init(void); // Sets up the LED IO ports
void Timer1Init(void); // Start Timer1

void toggle_red(void);
void toggle_green(void);
void toggle_blue(void);



