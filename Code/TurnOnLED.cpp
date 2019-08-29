#include "mbed.h"

DigitalOut green_led(PA_5);  //we could also say that it's located at D13. The recommendation is to use the MCU Pin Names

int main() {
    while(1) {
        green_led = 1; // LED is ON
        wait(1.0); // 200 ms
        green_led = 0; // LED is OFF
        wait(1.0); // 1 sec
    }
}
