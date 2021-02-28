#include "includesOther.h"  // inkluderar min h fil med includes 

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
//------------------------------//
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
