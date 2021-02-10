#include "certs.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <RH_ASK.h>
#include <SPI.h>

#define AWS_IOT_TOPIC_SUB "toilet"
#define AWS_IOT_TOPIC_PUB "iotKitchen"
#define tempDiff 0.5

static bool _connected = false;

float currentTemp = 0;
float previousTemp = 0;

char * deviceName = "ESPDEV";
char * ssid = "Gurka";
char * pass = "gintonic";
char * connection = "asn1gih30o3yg-ats.iot.eu-north-1.amazonaws.com";
char postNord[100];

RH_ASK driver(2000, 4, 5, 0);
WiFiClientSecure espClient = WiFiClientSecure();
PubSubClient client(espClient);



void setup()
{
  initSerial();
  if (!driver.init())
  {
    Serial.println("init failed");
  }
  initWifi();
  initAws();
}

void loop() {
  if (_connected)
  {
    uint8_t temp[30];
    uint8_t buflen = sizeof(temp);

    if (driver.recv(temp, &buflen))
    {
      DynamicJsonDocument doc(1000);
      DeserializationError err = deserializeJson(doc, (char*)temp);

      if (err)
      {
        Serial.print("jsonError");
        Serial.println(err.c_str());
        return;
      }
      currentTemp = doc["Temp"];
      serializeJson(doc, postNord);
    }

    Serial.print("postNord");
    Serial.println(postNord);
    if (currentTemp > (previousTemp + tempDiff) || currentTemp < (previousTemp - tempDiff))
    {
      Serial.print("current temp");
      Serial.println(currentTemp);
      Serial.print("previous temp");
      Serial.println(previousTemp);
      
      if (publishMessage(postNord))
      {
        Serial.println("sent ok");
      }
      
      else 
      {Serial.println("not sent");}

      //delay(10 * 1000);
      previousTemp = currentTemp;
    }
  }
  client.loop();
  delay(2222);
}
