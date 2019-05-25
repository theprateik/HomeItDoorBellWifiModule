#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Hive";
const char* password = "25DarkCoffee";
 
int inputPin = 5;
int outputPin = LED_BUILTIN;
bool isProcessing = false;
void setup () {
   pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

Serial.begin(9600);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}
 
void loop() {
  int sensorValue = digitalRead(inputPin);


  if (WiFi.status() == WL_CONNECTED && sensorValue > 0 && isProcessing == false) { //Check WiFi connection status
  isProcessing = true;
    digitalWrite(outputPin,LOW);
    
    // print out the value you read:
    Serial.println(sensorValue);


    HTTPClient http;  //Declare an object of class HTTPClient
    
    http.begin("http://192.168.1.213/api/doorbell/ring");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println("Sending Request...");
    Serial.println(httpCode);
    if (httpCode > 0) { //Check the returning code
    
      // String payload = http.getString();   //Get the request response payload
      // Serial.println(payload);                     //Print the response payload
  
    }
    http.end();   //Close connection
    isProcessing = false;
    delay(1000);
  }
  digitalWrite(outputPin,HIGH);
  //delay(5);    //Send a request every 30 seconds
}
