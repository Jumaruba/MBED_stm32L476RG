#include "mbed.h"

DigitalOut myled(PA_5);
DigitalIn mybutton(PC_13); 

int main() {
    while(1) {
   #if 0     
        if (mybutton == 0)     
            myled = 1;          
        if (mybutton == 1)
            myled = 0; 
            
#endif 
        myled = 1;
        wait(1.0);
        myled = 0; 
    }
}
