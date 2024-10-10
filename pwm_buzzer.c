/*
 * pwm_buzzer.c
 *
 *  Created on: Mar 25, 2024
 *      Author: bijoy
 */
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>
#include "pwm_buzzer.h"

#define WTIMER0          WTIMER0_BASE
#define PORTC           GPIO_PORTC_BASE
#define BUZZER_PERIPH   SYSCTL_PERIPH_GPIOC
#define BUZZER_PORT     GPIO_PORTC_BASE
#define BUZZER_PIN      GPIO_PIN_5

void PwmBuzzerInit(){
// Enable Wide timer 0
   SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);

   SysCtlPeripheralEnable(BUZZER_PERIPH);
   GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);

// Connect pins to the timers
   GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_5);
   GPIOPinConfigure(GPIO_PC5_WT0CCP1);

// Select PWM for Timer's 2-5 sub-timers A & B for each included
   TimerConfigure(WTIMER0, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM));

// Invert the PWM waveform, so that the match register value is the pulse width.
   TimerControlLevel(WTIMER0, TIMER_B, true);

// Enable Timer' 2-5 TimerA and TimerB
   TimerEnable(WTIMER0, TIMER_B);
}

void PwmBuzzerset(int pulse_Period, int pulse_Width){
// set the PWM parameters and buzzer
    TimerLoadSet(WTIMER0_BASE, TIMER_B, pulse_Period);
    TimerMatchSet(WTIMER0_BASE, TIMER_B, pulse_Width);
}
