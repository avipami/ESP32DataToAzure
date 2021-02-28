void messageCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("INCOMMING: ");
  //om vi ska ta emot och skriva ut saker kan vi lägga det här
}

void initAws()//i denna process tar vi kontakt med aws servrar där det kontrolleras att vi har alla rätta nycklar. Därefter väntar vi på svar
{
  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(connection, 8883);
  client.setCallback(messageCallback);

  Serial.print("Connecting to AWS IOT CORE");

  while (!client.connect(deviceName))
  {
    Serial.print(".");
    delay(1000);
  }

  if (!client.connected()) {
    Serial.println("\nTimeout");
    _connected = false;
    return;
  }

  else
  {
    _connected = true;
  }

  client.subscribe(AWS_IOT_TOPIC_SUB);//för att vi ska kunna lyssna på vad AWS gudarna har att säga behövs detta

  Serial.println("\nConnected to AWS IOT CORE");
}

bool publishMessage(char* postNord)
{
  if (client.publish(AWS_IOT_TOPIC_PUB, postNord)) // för att tala till gudarna och skicka magiska formler behöver vi denna funktion 
  {
    return true;
  }
  else return false;
}
