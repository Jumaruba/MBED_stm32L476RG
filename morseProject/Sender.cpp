#include "mbed.h"
#include <string>
#include "TextLCD.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(SERIAL_TX, SERIAL_RX);

InterruptIn btn(PC_13);
PwmOut receiver(PA_0);

DigitalOut led1(D12);       //checks if the buttom is pressed
DigitalOut led2(D11);       //checks if the buttom is pressed for 2 seconds
DigitalOut led3(D10);

Timer t;
Timer t2;

bool runOnce=true;
void toggle(void);
void toggle2(void);

int btnstate=5;


//DISPLAY
TextLCD lcd(D8, D3, D4, D5, D6,D7, TextLCD::LCD8x2);    //setting up the LCD

//arrays for morse translation
string letters[] = {"0122","1000","1010","1002","0222", "0010","1102","0000","0022","0111","1012","0100","1122","1022","1112","0110","1101","0102","0002","1222","0012","0001","0112","1001","1011","1100"};
string c[] = {"A","B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
string s;

int main()
{
    btn.rise(&toggle);  //wenn rauf
    btn.fall(&toggle2); //wenn runer
    
    //LED's off
    led1 = 1;
    led2=1;
    led3=1;
    
    pc.printf("Start!\n\r");
    receiver.period(4.0f);
    receiver.write(0.5f);

    //DISPLAY--------------------------------------

    //configuring the LCD --BEGIN--
    lcd.cls();
    lcd.setContrast(00);
    lcd.setInvert(true);
    //configuring the LCD --END--
    int array[4]= {0,1,2,2};
    for(int j=0; j<4; j++) {
        //transforming array into a string
        s.push_back(array[j]+48);
    }

    //printing the result on LCD
    for (int i = 0; i < 26; i++) {
        if (s == letters[i])
            lcd.printf("%s   %s", letters[i], c[i]);
    }
    //reseting the variable
    s = "";
    //DISPLAY END---------------------------------- need some changing
    
    while(1) {
        if(btnstate>=5) {
            receiver.write(0.5f); //standard signal
        }
        runOnce=true;            //debounce
        t2.reset();

        if(btnstate==4) {       //if sent 4 signals
            pc.printf("seq sent, wait 2 sec\n\r");
            btnstate++;
            wait(3);
        }

    }
}

void toggle2()   //if pressed down
{
    t2.start();//for debounce damit nicht mehrfach aufgerufen wenn btn loslassen
    if(runOnce == true) {
        t.start();
        led1 = 1;
        led2=1;
        led3=0;
        if(btnstate>=4) btnstate=0;
    }
    if(t2.read() > 0.01) { //100ms pause
        runOnce=true;
        t2.reset();
    }
}

void toggle()   //wenn wieder hoch
{
    t2.start();//for debounce damit nicht mehrfach aufgerufen wenn btn loslassen
    if(runOnce == true && btnstate<4) {
        led1=1;
        led2=1;
        led3=1;
        t.stop();
        printf("The time taken was %f seconds.\r\n", t.read());
        if(t.read()>=1.5) {
            receiver.write(0.75f);
            pc.printf("this is  1\n\r");
        } else {
            receiver.write(0.25f);
            pc.printf("this is  0\n\r");
        }
        btnstate++;
        //t3.start();

        t.reset();
        //receiver.write(0.5f);
        runOnce = false; //so kann incht nochmal code aufrufen
    }
    if(t2.read() > 0.01) { //100ms pause
        runOnce=true;
        t2.reset();
    }



}
