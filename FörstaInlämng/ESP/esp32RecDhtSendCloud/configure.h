void initSerial() {
  Serial.begin(115200);
  delay(2000);
}

void initWifi() {
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("\nIP Address: ");
  Serial.println(WiFi.localIP());
}


void initTime() {
  time_t epochTime;
  configTime(0,0,"pool.ntp.org", "time.nist.gov");

  while(true) {
    epochTime = time(NULL);

    if(epochTime == 28800) {
      delay(2000);
    } else {
      Serial.printf("NTP Time: %lu", epochTime);
      break;
    }
  }
}
