#include "mbed.h"
#include <ShiftReg.h>

#define latch p19
#define Clock p20
#define Data p18
DigitalIn BUTTONDown(p21);
DigitalIn BUTTONUp(p22);
int lastStateUp = 0;  // the previous state from the input pin
int currentStateUp; 
int lastStateDown = 0;  // the previous state from the input pin
int currentStateDown; 
char table[]=
{
//B-(dp)-G-F-E-D-C-B-A  

0B00111111 , // = 0 C
0B00000110 , // = 1 C
0B01011011 , // = 2 C
0B01001111 , // = 3 C
0B01100110 , // = 4 C
0B01101101 , // = 5 C
0B01111101 , // = 6 C
0B00000111 , // = 7 C
0B01111111 , // = 8 C
0B01101111 , // = 9 C
0B01110111 , // = A C
0B01111100 , // = B C
0B00111001 , // = C C
0B01011110 , // = D C
0B01111001 , // = E C
0B01110001 , // = F C
0B00000000 , // = Blank


};
 ShiftReg   HC595(Data, latch, Clock);
void Display(char num)
{

HC595.ShiftByte(table[num], ShiftReg::MSBFirst); HC595.Latch();
  
}


 
 int main() 
 {
     int count = 0;

     HC595.ShiftByte(0x00, ShiftReg::MSBFirst); HC595.Latch(); ThisThread::sleep_for(200);
     
     while(1) 
     {
        currentStateUp = BUTTONUp.read();
        currentStateDown = BUTTONDown.read();

        if(lastStateUp == 1 && currentStateUp == 0 && count < 9)
        {
            count = count +1;
        }
        if(lastStateDown == 1 && currentStateDown == 0 && count > 0)
        {
            count = count -1;
        }
            



        lastStateUp = currentStateUp;
        lastStateDown = currentStateDown;  
        Display(count); 
    }


 }
 
