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
  if(v1 < 600 && v2 >= 50 && v2 <= 70 && v3 >= 21 && v3 <= 24 && v4 >= 40 && v4 <= 60)
    return 1;
  else
    return 0;
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
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. 🙁");
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

float LightLevel;
float SoilMoist;
float Temp;
float Humidity;


void loop() {
  if(count >= 10) {
    bool flag = 0;
    int len = client.available();
    if (len > 0) {
      byte buffer[80];
      if (len > 80) len = 80;
      client.read(buffer, len);
      if (printWebData) {
        Serial.write(buffer, len); // show in the serial monitor (slows some boards)
      }
      byteCount = byteCount + len;
    }
    Serial.println();
    delay(1000);
    // Get sensor measurements
    
    getSensorMeasurements(Light_array, Soil_array, Temperature_array, Humidity_array);
    delay(2000);
    // Check if water pump is needed
    flag = water(LightLevel, SoilMoist, Temp, Humidity);
    delay(1000);
    // Send data to server
    sendSensorDataToServer(LightLevel, SoilMoist, Temp, Humidity, flag);
    delay(1000);
    if(flag) {
      Serial.write('<');
      Serial.write('\n');
      delay(3000);
    }
    count = 0;

    delay(6000);
  }
  else {
    // Measure sensors
    measureSensors();
    count++;
    delay(20000);
  }
}

void getSensorMeasurements(float Light_array[], float Soil_array[], float Temperature_array[], float Humidity_array[]) {
  LightLevel = average(Light_array, 10);
  delay(1000);
  SoilMoist = average(Soil_array, 10);
  delay(1000);
  Temp = average(Temperature_array, 10);
  delay(1000);
  Humidity = average(Humidity_array, 10);
  delay(1000);
  Serial.println(LightLevel);
  Serial.println(SoilMoist);
  Serial.println(Temp);
  Serial.println(Humidity);
  delay(1000);
}

void measureSensors() {
  Serial.println("Measuring...");
  delay(500);
  
  // Measure soil moisture
  digitalWrite(sensorPower, HIGH);
  delay(10);
  int soilMoisture = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);

  // Add soil moisture value to array
  float moisture_percentage = (100 - ((soilMoisture / 1023.00) * 100));
  Soil_array[count] = moisture_percentage;

  // Print soil moisture value for debugging
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // Measure temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Add temperature and humidity values to arrays
  Temperature_array[count] = temperature;
  Humidity_array[count] = humidity;

  // Measure light level
  int lightLevel = analogRead(IN_A0);
  bool lightStatus = digitalRead(IN_D0);

  // Add light level value to array
  Light_array[count] = lightLevel;

  delay(1000);
}


void sendSensorDataToServer(float LightLevel, float SoilMoist, float Temp, float Humidity, bool flag) {
  if (client.connect(server, 80)) {
    String postData = "LightLevel=" + String(LightLevel) + "&SoilMoist=" + String(SoilMoist) + "&Temp=" + String(Temp) + "&Humidity=" + String(Humidity) + "&WaterFlag=" + (flag ? "Yes": "No") ;
    client.println("POST /arduino/insert_data.php HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);
    client.println();
    Serial.println("POST sent");
    delay(5000);
    client.stop();
  } 
  else {
    Serial.println("Connection failed");
  }
}