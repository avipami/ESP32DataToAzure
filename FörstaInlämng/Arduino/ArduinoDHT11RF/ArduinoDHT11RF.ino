
//   Inlämning ArduinoKod DHT
//-----------------------------------//
// Bibliotek och definieringar
#include <Adafruit_Sensor.h>
#include <RH_ASK.h>
#include <DHT.h>
#include <SPI.h>
#define DHT_PIN 8
#define DHT_TYPE DHT11

//-----------------------------------//

RH_ASK dhlCargo(2000, 2, 2, 0);//skapar en instans av rh ask "driver" som heter dhl cargo.
DHT dht(DHT_PIN, DHT_TYPE);//skapar en instans av DHT med namd dht och sätter in pin och typ av sensor

void setup() {
  Serial.begin(115200); // initiering för seriell monitor
  dhlCargo.init();//initierar rf 
  dht.begin();//initierar dht sensor
}

void loop() {

  char temperature[10];
  char humidity [10];
  dtostrf(dht.readTemperature(), 3, 1, temperature); // tar temp data o lägger int med en decimal till temperature
  dtostrf(dht.readHumidity(), 3, 1, humidity);//samma som ovan fast fuktdata

//-----------------------------------//
// Denna sektion formaterar inhämtad dht data till en json sträng
  char msg[128] = "{\"Temp\":"; // H
  
  strcat(msg, temperature);
  strcat(msg, ",\"Hum\":");
  strcat(msg, humidity);
  strcat(msg, "}");
//-----------------------------------//
  
  Serial.println(msg); 
  dhlCargo.send((uint8_t *)msg, strlen(msg)); //Här skickas datat via rf eller ett dhl cargo plane
  dhlCargo.waitPacketSent();//vänta tills datat är skickat
 
  delay(5000);

}
