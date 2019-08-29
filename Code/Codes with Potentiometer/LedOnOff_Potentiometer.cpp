/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

DigitalOut led_D1( PA_5 ); 
DigitalIn potentiometer( PA_0 ); 

#define LED_ON 0
#define LED_OFF 1
// main() runs in its own thread in the OS
int main()
{
	while(true){
		if (!potentiometer){
			led_D1 = LED_OFF; 
		} else 
			led_D1 = LED_ON; 
	}
}
