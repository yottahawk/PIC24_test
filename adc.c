/*
 * File:   adc.c
 * Author: Harry Callahan
 *
 * Created on 24 December 2015, 11:14
 */

#include "main.h"

//initialisations
int adc_pot;

void InitADC(void)
{
    AD1PCFGLbits.PCFG0  = 0;        // Set AN0 pin as analog
    AD1CON1             = 0x20E2;   // Off, auto-convert
    AD1CON2             = 0;        // AVdd, AVss, int every conversion, MUXA only
    AD1CON3             = 0x1F05;   // 31 Tad auto-sample, Tad = 5*Tcy
    // AD1CON3             = 0x0100;   // Configure sample time = 1Tad,
                                    // A/D conversion clock as Tcy
    AD1CHS              = 0x0;      // MUXA uses AN0
    AD1CSSL             = 0;        // No scanned inputs
    
    AD1CON1bits.ADON    = 1;        // Start sampling
}

void ReadPotentiometer(void)
{
    AD1CON1bits.SAMP = 1;         // Start sampling, then auto-convert
    
    while (!AD1CON1bits.DONE);       // Wait
    adc_pot              = ADC1BUF0;
    
}
