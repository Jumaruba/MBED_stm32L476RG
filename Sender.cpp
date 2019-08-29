#include "mbed.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(SERIAL_TX, SERIAL_RX);

InterruptIn btn(PC_13);
DigitalOut led(PA_5);
PwmOut receiver(PA_0);
DigitalOut led1(D12); 		//checks if the buttom is pressed 
DigitalOut led2(D11);  		//checks if the buttom is pressed for 2 seconds
DigitalOut led3(D10); 
/*PwmOut ledBlue(PA_5);
PwmOut ledGreen(PA_6);
PwmOut ledRed(PA_7);*/

Timer t;
bool pushed = false;

void toggle(void);



int main()
{
    led=1;
    pc.printf("Start!");
    while(1) {
        receiver.period(4.0f);
        receiver.write(0.5f);
        for(int i=0; i<4; i++) {
            while(btn==1);
            if(!btn && !pushed) {
                t.start();

                led1 = 1; 				//if the button is pressed, turn on. 

                btn.rise(&toggle);
                pc.printf("btn pressed\n\r");
                pushed = true;
            } else if(btn && pushed) {
                btn.rise(&toggle);
            }
            
            wait(3);
            pc.printf("wait 2 sec for next input\n\r");
        }
        pc.printf("sending ... wait 8sec\n\r");
        wait(8);
    }
}

void toggle()
{
    if(t.read_ms()>200) {

    	led1 = 0; 						//if the buttom rises, turn off. 
    	
        t.stop();
        printf("The time taken was %f seconds.\r\n", t.read());
        if(t.read()>=1.5) {
            receiver.write(0.75f);
            pc.printf("this is  1\n\r");
        } else if(t.read()<1.5) {
            receiver.write(0.25f);
            
            pc.printf("this is  0\n\r");
        } else {
            receiver.write(0.5f);
            pc.printf("error");
        }
        
        t.reset();
        receiver.write(0.5f);
        pushed = false;
    }
}
