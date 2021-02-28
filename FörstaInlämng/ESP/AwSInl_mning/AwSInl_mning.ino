// Välkommen till magins land.. För att vi ska kunna nå en uppkoppling med AWS gudarna
// måste några saker till
// I certs.h behöver du lägga in nycklarna till AWS portarna
// I includes_others.h måste det till en annan nyckel i connection
// Glöm ej att namnge dina gudars namn och lösenordet för uppkoppling i ssid och pass under includes_others.h
// Vilken devicename du har måste även anges 

#include "includes_others.h"

void setup()
{
  initSerial();
  if (!driver.init())
  {
    Serial.println("init failed");
  }
  initWifi();//initierar en andlig koppling
  initAws();//initierar uppkoppling med molnen
}

void loop() {
  if (_connected)
  {
    uint8_t temp[30];
    uint8_t buflen = sizeof(temp);

    if (driver.recv(temp, &buflen))//här tar vi emot magiska formler från luften
    {
      DynamicJsonDocument doc(1000);//Spellbook som kan innehålla allt eller inget
      DeserializationError err = deserializeJson(doc, (char*)temp);//lägger in en trollformel skickad via luften

      if (err)
      {
        Serial.print("jsonError");
        Serial.println(err.c_str());
        return;
      }
      currentTemp = doc["Temp"];//ur den magiska boken tar vi ut ett värde som vi lägger åt sidan.
      serializeJson(doc, postNord);//kastar tillbaka alla formler på sin plats och stänger boken. med en kopia skickas den med postNord
    }

    Serial.println(postNord);//här kontrollerar vi att formeln som ska skickas är korrekt
    if (currentTemp > (previousTemp + tempDiff) || currentTemp < (previousTemp - tempDiff))//en magisk formel för att förhindra fri passage till molnen
    {
      Serial.print("current temp");
      Serial.println(currentTemp);
      Serial.print("previous temp");
      Serial.println(previousTemp);
      
      if (publishMessage(postNord))//skickar boken med postNord för vidare transport
      {
        Serial.println("sent ok");
      }
      
      else 
      {Serial.println("not sent");}

      //delay(10 * 1000);
      previousTemp = currentTemp;
    }
  }
  client.loop();//för kontroll av incoming och publish data och uppkoppling
  delay(2222);
}
