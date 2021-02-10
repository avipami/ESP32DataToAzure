void initSerial()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("");
}

void initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("-");
  }

  Serial.print("\nIP ADDRESS : ");
  Serial.println(WiFi.localIP());
}
