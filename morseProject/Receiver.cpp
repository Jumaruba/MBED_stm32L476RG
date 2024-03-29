#include "mbed.h"
#include "PwmIn.h"
#include <string>
#include "TextLCD.h"

Serial pc(SERIAL_TX, SERIAL_RX);

//DISPLAY -----------------------
TextLCD lcd(D8, D3, D4, D5, D6,D7, TextLCD::LCD8x2);    //setting up the LCD

//arrays for morse translation
string letters[] = {"0122","1000","1010","1002","0222", "0010","1102","0000","0022","0111","1012","0100","1122","1022","1112","0110","1101","0102","0002","1222","0012","0001","0112","1001","1011","1100"};
string c[] = {"A","B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
string s;
bool ok = false;

//END ---------------------

PwmIn input (PC_0);
int i=0;

//Working Project
int main()
{
    int array[4]= {2,2,2,2};    //empty array

    //configuring the LCD --BEGIN--
    lcd.cls();
    lcd.setContrast(00);
    lcd.setInvert(true);
    //configuring the LCD --END--

    int i = 0;
    
    pc.printf("Morse Code!\n");
    
    while(1) {
        for(int x=0; x<4; x++) {
            
            input.period();    
            input.pulsewidth();
            
            //reading the input
            while(input.dutycycle()<0.2 ||input.dutycycle()>0.3 && input.dutycycle()<0.7 ||input.dutycycle()>0.8) {
                input.period();
                input.pulsewidth();

            }

            float duty = input.dutycycle();

            if(input.dutycycle() > 0.72 && input.dutycycle()<0.79) {
                array[i]=1;
                pc.printf("receiving 0.75\n\r");
            } else if(input.dutycycle()> 0.22 && input.dutycycle() <0.29) {
                array[i]=0;
                pc.printf("receiving 0.25\n\r");

            } else {
                array[i]=2;
                pc.printf("dutycyle: %f\n\r",input.dutycycle());
            }

            wait(4);

            i++;
        }
        
        //storing information in the array
        if(i==4) {
            for(int j=0; j<4; j++) {
                pc.printf("array[%c]: %i\n\r\r\r\r", j, array[j]);
                s.push_back(array[j]+48);
                array[j]=2;
                i=0;
            }
            
            //printing the result on LCD
            for (int i = 0; i < 26; i++) {
                if (s == letters[i]) {
                    lcd.printf("%s   %s", letters[i], c[i]);
                    ok = true;
                }
            }
            if (!ok)
                lcd.printf("ERROR!");

        }
        s = "";
        wait(2);
    }
}
