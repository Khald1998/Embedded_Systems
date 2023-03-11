

int latch=3;  //74HC595  pin 3 STCP
int clock=4; //74HC595  pin 4 SHCP
int data=2;   //74HC595  pin 2 DS
int BUTTONDown = 9;
int BUTTONUp = 8;
int lastStateUp = LOW;  // the previous state from the input pin
int currentStateUp; 
int lastStateDown = LOW;  // the previous state from the input pin
int currentStateDown; 
int count = 0;

byte table[]=
{
//B-(dp)-G-F-E-D-C-B-A  

B00111111 , // = 0 C
B00000110 , // = 1 C
B01011011 , // = 2 C
B01001111 , // = 3 C
B01100110 , // = 4 C
B01101101 , // = 5 C
B01111101 , // = 6 C
B00000111 , // = 7 C
B01111111 , // = 8 C
B01101111 , // = 9 C
B01110111 , // = A C
B01111100 , // = B C
B00111001 , // = C C
B01011110 , // = D C
B01111001 , // = E C
B01110001 , // = F C
B00000000 , // = Blank


};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(BUTTONDown, INPUT);
  pinMode(BUTTONUp, INPUT);    
}
void Display(byte num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}
void loop() {

    currentStateUp = digitalRead(BUTTONUp);
    currentStateDown = digitalRead(BUTTONDown);


  if(lastStateUp == HIGH && currentStateUp == LOW && count < 9)

count = count +1;
  if(lastStateDown == HIGH && currentStateDown == LOW && count > 0)
count = count -1;


  lastStateUp = currentStateUp;
  lastStateDown = currentStateDown;  
Display(count); 
}
