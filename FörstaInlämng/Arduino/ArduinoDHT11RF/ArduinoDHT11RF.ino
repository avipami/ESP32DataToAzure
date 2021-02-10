#include <Adafruit_Sensor.h>
#include <RH_ASK.h>
#include <DHT.h>
#include <SPI.h>
#define DHT_PIN 8
#define DHT_TYPE DHT11


RH_ASK dhlCargo(2000, 2, 2, 0);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dhlCargo.init();
  dht.begin();
}

void loop() {

  char temperature[10];
  char humidity [10];
  dtostrf(dht.readTemperature(), 3, 1, temperature);
  dtostrf(dht.readHumidity(), 3, 1, humidity);
  //strcpy(temperature,String(dht.readTemperature(), 2).c_str());
  //strcpy(humidity,String(dht.readHumidity(), 2).c_str());
  char msg[128] = "{\"Temp\":";
  
  strcat(msg, temperature);
  strcat(msg, ",\"Hum\":");
  strcat(msg, humidity);
  strcat(msg, "}");

  //Serial.print(F("Temperature: "));
  //Serial.print(temperature);
  //Serial.print(F(", Humidity: "));
  //Serial.println(humidity);
  Serial.println(msg);
  dhlCargo.send((uint8_t *)msg, strlen(msg));
  dhlCargo.waitPacketSent();
 
  delay(5000);

}
