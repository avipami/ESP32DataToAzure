#include "configure.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  init.dhlCargo();
  initSerial();
  initWifi();
  initTime();
  initIotDevice();
}

int count = 0;

void loop() {
  if(!messagePending && messageSending) {
    
    char payload[128];
    snprintf(payload, 128, "Message #%2ld", ++count);

    sendIotMessage(payload);
    delay(5 * 1000);   
  }

  IoTHubClient_LL_DoWork(deviceClient);
  delay(10);
}
