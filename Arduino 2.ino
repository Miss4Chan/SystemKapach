const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
#define pumppin 13

char mystr[10];

void setup ()
  { 
  pinMode(pumppin,OUTPUT);
  Serial.begin (115200);
  Serial.println("Starting...");
  } // end of setup
  
void loop ()
  { // end of for
  char mystr = Serial.read();
  if(mystr == '<')
  {
  
  delay(1000);
  digitalWrite(pumppin,HIGH);
  delay(1000);
  Serial.println("finished pumping");
  digitalWrite(pumppin,LOW);
  delay (5000);
  }
  }  // end of loop