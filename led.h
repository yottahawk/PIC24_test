/* 
 * File: main.c   
 * Author: Harry Callahan
 * Comments: A test project for experimenting with programming of the PIC24FJ256GB106 in the starter kit.
 * Revision history: 
 */

//Function prototypes

void Led_Cycle_Start(void);         // Start cyclical flashing of LED's.

void LedDigital_IO_Init(void);      // Sets up the LED IO ports
void Timer1Init(void);              // Start Timer1
void Timer1period(int period);      // Set Timer1 period to new value

void Cycle_Flash(void);             // Switches consecutive Led's off/on

void toggle_red(void);              // Switches one colour led off/on
void toggle_green(void);
void toggle_blue(void);



