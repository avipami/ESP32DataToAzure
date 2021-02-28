void initWiFi()
{
    WiFi.begin(ssid,pass); // drar igång kopplingen mellan datorn o vindkraftverken 
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("."); 
  }
  Serial.println("\nIP Address: ");
  Serial.println(WiFi.localIP());
}
