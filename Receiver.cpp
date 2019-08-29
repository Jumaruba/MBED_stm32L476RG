#include "mbed.h"
#include "PwmIn.h"
#include <string> 
#include "TextLCD.h"


Serial pc(SERIAL_TX, SERIAL_RX);


TextLCD lcd(D8, D3, D4, D5, D6,D7, TextLCD::LCD8x2);    //setting up the LCD

//arrays for morse translation 
string letters[] = {"0122","1000","1010","1002","0222", "0010","1102","0000","0022","0111","1012","0100","1122","1022","1112","0110","1101","0102","0002","1222","0012","0001","0112","1001","1011","1100"};
string c[] = {"A","B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"}; 
string s;

PwmIn input (PC_0);
int x=0;
int i=0;


int main()
{   
    //configuring the LCD --BEGIN--
    lcd.cls();
    lcd.setContrast(00); 
    lcd.setInvert(true);  
    servo.period(2); 
    //configuring the LCD --END--
    
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
                 //transforming array into a string
                s.push_back(array[j]+48); 
                
                pc.printf("array[%c]: %i\n\r\r\r\r", j, array[j]);
                array[j]=2;
                i=0;
                
            }
                //printing the result on LCD
                for (int i = 0; i < 26; i++){
                     if (s == letters[i])
                        lcd.printf("%s   %s", letters[i], c[i]);
                }
            //reseting the variable
            s = ""; 
            
            wait(8);
        }
        

    }
}
