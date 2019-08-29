#include "mbed.h"
#include "PwmIn.h"

Serial pc(SERIAL_TX, SERIAL_RX);

PwmIn input (PC_0);
int x=0;
int i=0;
bool can;

void increase()
{
    i++;
}
int main()
{
    int array[4]= {2,2,2,2};
    int i = 0;
    pc.printf("Hello World !\n");
    while(1) {
        for(int x=0; x<4; x++) {
            input.period();
            input.pulsewidth();
            while(input.dutycycle()<0.2 
                ||input.dutycycle()>0.3 && input.dutycycle()<0.7
                ||input.dutycycle()>0.8){
            
                input.period();
            }
            
            input.pulsewidth();
            if(input.dutycycle() >0.72 && input.dutycycle()<0.79) {
                array[i]=1;

                /*if (can)
                    increase();
                can = false;  */
                pc.printf("receiving 0.75\n\r");
            } else if(input.dutycycle()> 0.22 && input.dutycycle() <0.29) {
                array[i]=0;
                pc.printf("receiving 0.25\n\r");
                can = true;
            } else {
                array[i]=2;
                pc.printf("dutycyle: %f\n\r",input.dutycycle());
            }


            wait(2);
            i++;
        }
        if(i==4) {
            for(int j=0; j<4; j++) {
                pc.printf("array[%c]: %i\n\r\r\r\r", j, array[j]);
                array[j]=2;
                i=0;
            }
            wait(8);
        }

    }
}
