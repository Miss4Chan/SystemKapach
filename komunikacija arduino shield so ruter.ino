
#include <SPI.h>
#include <Ethernet.h>

#include <DHT.h>

#define DHTPIN 8     // Digital pin Temp&Hum sensor
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //mac of ethernet shield

char server[] = "192.168.100.37";    // address for the server 

IPAddress ip(192, 168, 100, 177); //static address in case of DHCP failure
IPAddress myDns(192, 168, 100, 1); //Local gateway

EthernetClient client;

int count=0;
float tempValues[10];

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setup() {
  Serial.begin(115200);
  dht.begin(); // Initialize DHT sensor

  Ethernet.init(10);  // Shield cs pin
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1);
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip, myDns);
  } else {
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

float average (float * array, int len) 
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ;  // average will be fractional, so float may be appropriate.
}

void loop() {
	

	if(count>=10)
	{
		avgHum = average(tempValues,sizeof(tempValues));
		float value1 = 5.23;
  		float value2 = 4.34;
  		float value3 = 3.45;
  		float value4 = avgHum;
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
  } else {
    Serial.println("Connection failed");
  }
	}
	else
	{
		float temperature = dht.readTemperature();
  		float humidity = dht.readHumidity();

  		if (isnan(temperature) || isnan(humidity)) {
    		Serial.println("Failed to read from DHT sensor!");
    	return;
    	delay(1000);
    	tempValues[count]=humidity;
    		Serial.print("Temperature: ");
  			Serial.print(temperature);
 			Serial.print(" °C, Humidity: ");
  			Serial.print(humidity);
  			Serial.println(" %");
  	}

//   // if there are incoming bytes available
//   // from the server, read them and print them:
//   int len = client.available();
//   if (len > 0) {
//     byte buffer[80];
//     if (len > 80) len = 80;
//     client.read(buffer, len);
//     if (printWebData) {
//       Serial.write(buffer, len); // show in the serial monitor (slows some boards)
//     }
//     byteCount = byteCount + len;
//   }
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
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