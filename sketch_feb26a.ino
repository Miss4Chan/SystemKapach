#include <math.h>
#include <SevSeg.h>
double a; // Variable to store decimal data
double Din; // Variable to store computed sensor data
int disp1=7; // 1st Digit of the display, (Left to Right) connected to PIN 1 of the Arduino
int disp2=4; // 2nd Digit of the display
int disp3=3; // 3rd Digit of the display
int segA=6; // Segment A of the LED display
int segB=2; // Segment B of the LED display
int segC=17; // Segment C of the LED display
int segD=15; // Segment D of the LED display
int segE=14; // Segment E of the LED display
int segF=5; // Segment F of the LED display
int segG=18; // Segment G of the LED display
int segDP=16; // Segment DP of the LED display
int disp4 = 19;

SevSeg sevseg;


void setup()
{
  Serial.begin(9600);
pinMode(disp1, OUTPUT);
pinMode(disp2, OUTPUT);
pinMode(disp3, OUTPUT);
pinMode(disp4,OUTPUT);
pinMode(segA, OUTPUT);
pinMode(segB, OUTPUT);
pinMode(segC, OUTPUT);
pinMode(segD, OUTPUT);
pinMode(segE, OUTPUT);
pinMode(segF, OUTPUT);
pinMode(segG, OUTPUT);
pinMode(segDP, OUTPUT);

}
void loop()
{
Din = 25.6;

a = fmod(Din,1.0); // Taking mod of Din
int temp = a * 10;

//Section to switch approperiate digit of the display based on computed data
clearLEDs();
digitalWrite(disp1,HIGH);
digitalWrite(disp2,HIGH);
digitalWrite(disp3,LOW);
digitalWrite(disp4,HIGH);
digitalWrite(segDP,LOW);
display(temp);
sevseg.refreshDisplay();
delay(5);


clearLEDs();
int temp1 = (int) fmod(Din,10);
digitalWrite(disp1,HIGH);
digitalWrite(disp2,LOW);
digitalWrite(disp3, HIGH);
digitalWrite(disp4,HIGH);
digitalWrite(segDP,HIGH);
display(temp1);
Serial.println(temp1);
sevseg.refreshDisplay();
delay(5);


clearLEDs();
int temp2 = Din/10;
digitalWrite(disp1,LOW);
digitalWrite(disp2,HIGH);
digitalWrite(disp3, HIGH);
digitalWrite(disp4,HIGH);
digitalWrite(segDP,LOW);
display(temp2);
Serial.println(temp2);
sevseg.refreshDisplay();
delay(5);


clearLEDs();
displayC();
delay(5);
}

int displayp()
{
#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3, HIGH);
  digitalWrite(disp4,LOW);
  digitalWrite(segDP,LOW);

    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
}

int displayC()
{

#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3,HIGH);
  digitalWrite(disp4,LOW);
  digitalWrite(segDP,LOW);

    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);  
}


int display (int a)
{
#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

   

   switch (a){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  }
}
void clearLEDs() //clear the 7-segment display screen
{
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segDP, LOW);
}
