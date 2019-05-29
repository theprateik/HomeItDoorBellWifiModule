
#include <ESP8266WiFi.h>
#include "SpiffsFunctions.h"
#include "WebServerFunctions.h"
#include "NetworkFunctions.h"
#include "HubFunctions.h"

int period = 1000;
unsigned long time_now = 0;

int inputPin = 5;
int outputPin = LED_BUILTIN;

void setup()
{
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect();

  startSPIFFS();
  startNetwork();
  startWebServer();

  if (NETWORK_AS_STATION == true)
  {
    Serial.println("Staring the Hub");
    startHub();
  }
}

void loop()
{
  if (NETWORK_AS_AP == true)
  {
    WebSocketServer.loop();
  }
  else if (NETWORK_AS_STATION == true)
  {
    int sensorValue = digitalRead(inputPin);
    websocketClientLoop();
    if (millis() > time_now + period && sensorValue > 0)
    {
        time_now = millis();

        Serial.println(sensorValue);
        
        digitalWrite(outputPin, LOW);
        
        ringBell();
    }
    digitalWrite(outputPin, HIGH);
  }
  WebServer.handleClient();
}