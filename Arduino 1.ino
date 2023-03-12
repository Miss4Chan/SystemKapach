
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 8     // Digital pin where the humidity and temperature sensor is connected 
#define DHTTYPE DHT22   

// Sensor pins for soil sensor
#define sensorPower 2
#define sensorPin A0

const int IN_A0 = A1; // Light sensor pins
const int IN_D0 = 5; 


using namespace std;

DHT dht(DHTPIN, DHTTYPE); //Initialize dht object 


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //mac of shield

char server[] = "13.81.0.251";    // name address for the server

// Set the static IP address to use if the DHCP fails to assign
 IPAddress ip(192, 168, 100, 177);
 IPAddress myDns(192, 168, 100, 1);
EthernetClient client; //Ethernet client initializtion

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

bool water(float v1,float v2,float v3,float v4)
{
  //algorithm and logic :))
  return 1;
}

float average(float a[], int n){
  int sum = 0;
  for(int i=0; i<n;i++){
    sum += a[i];
  }
  return (float)sum/n;
}

void setup() {
  Serial.begin(115200); //BAUS rate where DHT works -->  use for everything
  dht.begin(); // Initialize DHT sensor

  pinMode (IN_A0, INPUT);
  pinMode (IN_D0, INPUT);
  
  Ethernet.init(10);  // CS pin for Ethernet shield
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); //usually works
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } 
  else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  beginMicros = micros();
}

int value_A0;
bool value_D0;
int count = 0;

//Arrays to keep 10 measurements 
float Temperature_array[10];
float Humidity_array[10];
float Soil_array[10];
float Light_array[10];



void loop() {

  if(count>=10)
  {
    int len = client.available();
    if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;}
    
    delay(1000);
    float value1 = average(Light_array, 10);
      delay(1000);
    float value2 = average(Soil_array, 10);
      delay(1000);
    float value3 = average(Temperature_array, 10);
      delay(1000);
    float value4 = average(Humidity_array, 10);
      delay(1000);
    Serial.println(value1);
    Serial.println(value2);
    Serial.println(value3);
    Serial.println(value4);
    delay(1000);
    //Funckija proveri dali treba pump
    if (client.connect(server, 80)) {
      String postData = "value1=" + String(value1) + "&value2=" + String(value2) + "&value3=" + String(value3) + "&value4=" + String(value4);
      client.println("POST /arduino/insert_data.php HTTP/1.1");
      client.println("Host: " + String(server));
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(postData.length());
      client.println();
      client.println(postData);
      client.println();
      Serial.println("POST sent");
        delay(1000);
    } 
    else {
      Serial.println("Connection failed");
    }
    bool flag = 0;

    flag = water(value1,value2,value3,value4);
    delay(1000);
    if(flag)
    {
        Serial.write('<');
        delay(2000);
    }

  
    delay(1000);
  // if the server's disconnected, stop the client:
    if (!client.connected()) 
    {
      Serial.println("Client not connected");
      endMicros = micros();
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
      Serial.print("Received ");
      Serial.print(byteCount);
      Serial.print(" bytes in ");
      float seconds = (float)(endMicros - beginMicros) / 1000000.0;
      Serial.print(seconds, 4);
      float rate = (float)byteCount / seconds / 1000.0;
      Serial.print(", rate = ");
      Serial.print(rate);
      Serial.print(" kbytes/second");
      Serial.println();
      // do nothing forevermore:
      while (true) {
        delay(1);
        }
    }
      count=0;
      delay(1000);
  }
  else
  {
    //Temp and hum sesnsor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    //ensure measurements
    if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;}
    Temperature_array[count] = temperature;
    Humidity_array[count] = humidity;
    delay(2000);
    //Light sensor
    value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
    value_D0 = digitalRead(IN_D0);// reads the digital input from the IR distance sensor
    Light_array[count] = value_A0;
    //soil sensor
    delay(2000);
    digitalWrite(sensorPower, HIGH); // Turn the sensor ON
    delay(10); // Allow power to settle
    float val = analogRead(sensorPin); // Read the analog value from sensor
    float moisture_percentage = (100 - ((val / 1023.00) * 100));
    digitalWrite(sensorPower, LOW); // Turn the sensor OFF
    Soil_array[count]= moisture_percentage;
    delay(2000);

    //print values
    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.print(" °C, Humidity: ");
    // Serial.print(humidity);
    // Serial.println(" %");
    // Serial.print("Soil Moisture: ");
    // Serial.print(moisture_percentage);
    // Serial.println(" %");
    // Serial.print(" Analogue = "); 
    // Serial.print(value_A0);
    // Serial.print("\t Digital ="); 
    // Serial.println(value_D0);
    //Serial.println("Data measured");
    count++;
  }
}
