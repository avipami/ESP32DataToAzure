
void messageCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("INCOMMING: ");
}

void initAws()
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

  client.subscribe(AWS_IOT_TOPIC_SUB);

  Serial.println("\nConnected to AWS IOT CORE");
}

bool publishMessage(char* postNord)
{
  if(client.publish(AWS_IOT_TOPIC_PUB, postNord))
  {
  return true;
  }
  else return false;
}
