/*
 *  
 */

#include <ESP8266WiFi.h>

const char* ssid     = "HOME-7CE8";
const char* password = "H211351BB1401276";
const char* host = "api.pushingbox.com"; //http://api.pushingbox.com/pushingbox?devid=vBCC8E7598B28D70
const char* pushingbox = "api.pushingbox.com/pushingbox?devid=vBCC8E7598B28D70";
int status = WL_IDLE_STATUS;                     // the Wifi radio's status

const int PIR = 5;                       // the number of the PIR pin

// variables will change:
int PIRstate = 0;                        // a boolean variable for reading the PIRstate status
int value = 0;

void setup() {
// Initialize the BUILTIN_LED pin as an output
  pinMode(BUILTIN_LED, OUTPUT);
// Initialize GPIO 0 pin as an output
  //pinMode(0, OUTPUT);
// Initialize the PIR pin as an input:
  pinMode(PIR,INPUT);
  digitalWrite(PIR, LOW); //Seems to stop 
  
  Serial.begin(115200);
  delay(10);

// We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  // One time 45 second delay to allow PIR to "stabalize"
// Blinks GPIO0 LED slowly then quickly to show progress
Serial.println("Waiting to calibrate PIR");
digitalWrite(BUILTIN_LED, HIGH);
delay(5000);
digitalWrite(BUILTIN_LED, LOW);
delay(5000);
digitalWrite(BUILTIN_LED, HIGH);
delay(5000);
digitalWrite(BUILTIN_LED, LOW);
delay(5000);
digitalWrite(BUILTIN_LED, HIGH);
delay(5000);
digitalWrite(BUILTIN_LED, LOW);
delay(5000);
digitalWrite(BUILTIN_LED, HIGH);
delay(5000);
digitalWrite(BUILTIN_LED, LOW);
delay(5000);
digitalWrite(BUILTIN_LED, HIGH);
delay(1000);
digitalWrite(BUILTIN_LED, LOW);
delay(1000);
digitalWrite(BUILTIN_LED, HIGH);
delay(1000);
digitalWrite(BUILTIN_LED, LOW);
delay(1000);
digitalWrite(BUILTIN_LED, HIGH);
Serial.println("PIR Calibrated");
}

void loop() {
  
  ++value;

  PIRstate = digitalRead(PIR);          //read the state of the PIR value

  
// Use WiFiClient class to create TCP connections
//  WiFiClient client;
//  const int httpPort = 80;
//  if (!client.connect(host, httpPort)) {
//    Serial.println("connection failed");
//    //return;
//  }
  
// We now create a URI for the request
  String url = "/pushingbox?devid=vBCC8E7598B28D70";

// check if the PIR is senses movement.
// if it is, the PIRstate is HIGH and print "Motion Detected along with changing LED:
  if (PIRstate == HIGH) {
    Serial.println("Motion Detected");
// turn LED on:

    digitalWrite(BUILTIN_LED, LOW);
    
  WiFiClient client;
  const int httpPort = 80;  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting to resolve connection.");
    return;
  }
  
    Serial.print("connecting to ");
    Serial.println(host);
    Serial.print("Requesting URL: ");
    Serial.println(url);
// This will send the HTTP request to the server
    client.println("GET /pushingbox?devid=vBCC8E7598B28D70 HTTP/1.1");
    client.println("Host: api.pushingbox.com");
    client.println("Connection: close");
    client.println();
    //delay(10);
  //Serial.println("closing connection");
  //Serial.println("");
  //Since PIRstate is high wait 10 seconds to avoid repeatedly requesting push
  delay(10000);   
  }
  else{
  digitalWrite(BUILTIN_LED, HIGH);
  }
}
