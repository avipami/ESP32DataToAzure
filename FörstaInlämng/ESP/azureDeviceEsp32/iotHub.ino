void initIotHub()
{
  if (!Esp32MQTTClient_Init((const uint8_t *) connectionString))//kollar om länken till azure med nyckenl är godkänd
  {
    _connected = false;
    return;
  }
  else
  {
    _connected = true;
  }
}
