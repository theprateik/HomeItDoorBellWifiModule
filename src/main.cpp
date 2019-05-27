
#include <ESP8266WiFi.h>
#include "SpiffsFunctions.h"
#include "WebServerFunctions.h"
#include "NetworkFunctions.h"
#include "HubFunctions.h"

int inputPin = 5;
int outputPin = LED_BUILTIN;
bool isProcessing = false;

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

  if (NETWORK_AS_CLIENT == true)
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
  else if (NETWORK_AS_CLIENT == true)
  {
    int sensorValue = digitalRead(inputPin);
    websocketClientLoop();
    if (isProcessing == false && sensorValue > 0) 
    {
      isProcessing = true;
      digitalWrite(outputPin, LOW);
      // TODO: write code to ring bell here
      ringBell();

      isProcessing = false;
    }
    digitalWrite(outputPin, HIGH);
  }

  WebServer.handleClient();
}