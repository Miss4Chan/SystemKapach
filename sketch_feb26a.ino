#include <math.h>
#include <SevSeg.h>

#define ON  HIGH
#define OFF LOW
//Global variables and pins
double a; // Variable to store decimal data
double Din; // Variable to store computed sensor data
int disp1=7; // 1st Digit ofDigitisplayNumber, (Left to Right) connected to PIN 1 of the Arduino
int disp2=4; // 2nd Digit ofDigitisplayNumber
int disp3=3; // 3rd Digit ofDigitisplayNumber
int segA=6; // Segment A of theDigitisplayNumber
int segB=2; // Segment B of theDigitisplayNumber
int segC=17; // Segment C of theDigitisplayNumber
int segD=15; // Segment D of theDigitisplayNumber
int segE=14; // Segment E of theDigitisplayNumber
int segF=5; // Segment F of theDigitisplayNumber
int segG=18; // Segment G of theDigitisplayNumber
int segDP=16; // Segment DP of theDigitisplayNumber
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
  Din = 25.6; //Number inputed
  displayNumber(Din);
}


int diplayNumber()
{
   a = fmod(Din,1.0); // Taking mod of Din
  int temp = a * 10;

  clearLEDs();
  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3,LOW);
  digitalWrite(disp4,HIGH);
  digitalWrite(segDP,LOW);
  displayDigit(temp);
  sevseg.refreshDisplay();
  delay(5);

  clearLEDs();
  int temp1 = (int) fmod(Din,10);
  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,LOW);
  digitalWrite(disp3, HIGH);
  digitalWrite(disp4,HIGH);
  digitalWrite(segDP,HIGDigitisplayNumber(temp1);
  Serial.println(temp1);
  sevseg.refreshDisplay();
  delay(5);

  clearLEDs();
  int temp2 = Din/10;
  digitalWrite(disp1,LOW);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3, HIGH);
  digitalWrite(disp4,HIGH);
  digitalWrite(segDP,LODigitisplayNumber(temp2);
  Serial.println(temp2);
  sevseg.refreshDisplay();
  delay(5);


}
int displayLetter()
{
  if(flag==0)
  {
    clearLEDs();
    displayC();
    delay(5);
  }
  else
  {
    clearLEDs();
    displayP();
    delay(5);
  }
}

int displayP()
{
  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3, HIGH);
  digitalWrite(disp4,LOW);
  digitalWrite(segDP,LOW);

    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, OFF);
    digitalWrite(segD, OFF);
    digitalWrite(segE, ON);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
}

int displayC()
{

  digitalWrite(disp1,HIGH);
  digitalWrite(disp2,HIGH);
  digitalWrite(disp3,HIGH);
  digitalWrite(disp4,LOW);
  digitalWrite(segDP,LOW);

    digitalWrite(segA, ON);
    digitalWrite(segB, OFF);
    digitalWrite(segC, OFF);
    digitalWrite(segD, ON);
    digitalWrite(segE, ON);
    digitalWrite(segF, ON);
    digitalWrite(segG, OFF);  
}

DigitisplayNumber (int a)
{
  #define ON  HIGH
  #define OFF LOW
  switch (a){

    case 0:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, ON);
      digitalWrite(segF, ON);
      digitalWrite(segG, OFF);
      break;

    case 1:
      digitalWrite(segA, OFF);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, OFF);
      digitalWrite(segE, OFF);
      digitalWrite(segF, OFF);
      digitalWrite(segG, OFF);
      break;

    case 2:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, OFF);
      digitalWrite(segD, ON);
      digitalWrite(segE, ON);
      digitalWrite(segF, OFF);
      digitalWrite(segG, ON);
      break;

    case 3:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, OFF);
      digitalWrite(segF, OFF);
      digitalWrite(segG, ON);
      break;

    case 4:
      digitalWrite(segA, OFF);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, OFF);
      digitalWrite(segE, OFF);
      digitalWrite(segF, ON);
      digitalWrite(segG, ON);
      break;

    case 5:
      digitalWrite(segA, ON);
      digitalWrite(segB, OFF);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, OFF);
      digitalWrite(segF, ON);
      digitalWrite(segG, ON);
      break;

    case 6:
      digitalWrite(segA, ON);
      digitalWrite(segB, OFF);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, ON);
      digitalWrite(segF, ON);
      digitalWrite(segG, ON);
      break;

    case 7:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, OFF);
      digitalWrite(segE, OFF);
      digitalWrite(segF, OFF);
      digitalWrite(segG, OFF);
      break;

    case 8:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, ON);
      digitalWrite(segF, ON);
      digitalWrite(segG, ON);
      break;

    case 9:
      digitalWrite(segA, ON);
      digitalWrite(segB, ON);
      digitalWrite(segC, ON);
      digitalWrite(segD, ON);
      digitalWrite(segE, OFF);
      digitalWrite(segF, ON);
      digitalWrite(segG, ON);
      break;

    case 10:
      digitalWrite(segA, OFF);
      digitalWrite(segB, OFF);
      digitalWrite(segC, OFF);
      digitalWrite(segD, OFF);
      digitalWrite(segE, OFF);
      digitalWrite(segF, OFF);
      digitalWrite(segG, OFF);
      break;
  }
}
void clearLEDs() 
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