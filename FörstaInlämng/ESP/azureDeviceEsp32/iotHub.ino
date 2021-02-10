void initIotHub()
{
  if (!Esp32MQTTClient_Init((const uint8_t *) connectionString))
  {
    _connected = false;
    return;
  }
  else
  {
    _connected = true;
  }
}
