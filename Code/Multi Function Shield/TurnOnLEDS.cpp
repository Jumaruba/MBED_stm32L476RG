/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

/*This code turns on LEDS using the 3 buttons at the multifunction board shield*/

//LEDS
DigitalOut led_D1(PA_5);
DigitalOut led_D2(PA_6);
DigitalOut led_D3(PA_7);
DigitalOut led_D4(PB_6);
#define LED_ON 0
#define LED_OFF 1
//buttons
DigitalIn sw_S1(PA_1);
DigitalIn sw_S2(PA_4);
DigitalIn sw_S3(PB_0);



// main() runs in its own thread in the OS
int main()
{

	led_D1 = LED_OFF; 
    led_D2 = LED_OFF;
    led_D3 = LED_OFF; 
    led_D4 = LED_OFF; 
    
    while (true){
    	if (!sw_S1){
    		led_D1 = LED_ON; 
    	}else{
    		led_D1 = LED_OFF; 
    	}

    	if (!sw_S2){
    		led_D2 = LED_ON; 
    	}else{
    		led_D2 = LED_OFF; 
    	}

    	if (!sw_S3){
    		led_D3 = LED_ON; 
    		led_D4 = !led_D4; 
    	}else{
    		led_D3 = LED_OFF; 
    	}
    }
}
