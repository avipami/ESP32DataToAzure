#include <WiFi.h>
#include <Esp32MQTTClient.h>
#include <ArduinoJson.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 4, 5, 0); // skapar en instans av rh ask kallad driver där vi tilldelar rx port till 4

//------------------------------//
char* ssid = "Gurka";//wifi namn// <----------------------------------------------------
char* pass = "gintonic";//löösen// <----------------------------------------------------
char* connectionString = "SKRIV HÄR";//den speciella sträng för förbindelse med azure device// <----------------------------------------------------
static bool _connected = false;
//------------------------------//
//för den magiska formlen behöver vi detta

#define tempDiff 0.5
float currentTemp = 0;
float previousTemp = 0;
//------------------------------//
