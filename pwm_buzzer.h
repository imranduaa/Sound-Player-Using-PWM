/*
 * pwm_buzzer.h
 *
 *  Created on: Mar 25, 2024
 *      Author: bijoy
 */

#ifndef PWM_BUZZER_H_
#define PWM_BUZZER_H_
#include <stdint.h>

void PwmBuzzerInit();

void PwmBuzzerset(int pulse_Period, int pulse_Width);




#endif /* PWM_BUZZER_H_ */
