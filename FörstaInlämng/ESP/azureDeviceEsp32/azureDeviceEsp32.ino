#include "includesOther.h"
RH_ASK driver(2000, 4, 5, 0);

char* ssid = "Gurka";
char* pass = "gintonic";
char* connectionString = "HostName=vinniesEmpire.azure-devices.net;DeviceId=ESP32;SharedAccessKey=JNFUzY/jYd2RI7zdxWxGU3Gni6ZFHAN4FBJ1d4ya5jc=";
static bool _connected = false;

char payload[60];

#define tempDiff 0.5
float currentTemp = 0;
float previousTemp = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);

  if (!driver.init())
  {
    Serial.println("init failed");
  }
  initWiFi();
  initIotHub();
}
char postNord[100];
void loop()
{
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

    //char tempor[60];
    //strcpy(tempor, (char*)temp);
    //Serial.println(tempor);

    //snprintf(payload, 128, "Message Bajs # %21d", ++count);
    Serial.print("postNord");
    Serial.println(postNord);
    if (currentTemp > (previousTemp + tempDiff) || currentTemp < (previousTemp - tempDiff))
    {
      Serial.print("current temp");
      Serial.println(currentTemp);
      Serial.print("previous temp");
      Serial.println(previousTemp);
      if (Esp32MQTTClient_SendEvent(postNord))
        {
        Serial.println(postNord);
        }
      //delay(10 * 1000);
      previousTemp = currentTemp;
    }
  }
  delay(4000);
}
