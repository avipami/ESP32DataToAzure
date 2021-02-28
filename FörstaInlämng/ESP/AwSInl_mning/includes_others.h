#include "certs.h" // självförklarande :P

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <RH_ASK.h>
#include <SPI.h>

#define AWS_IOT_TOPIC_SUB "toilet"
#define AWS_IOT_TOPIC_PUB "iotKitchen"
#define tempDiff 0.5

static bool _connected = false;

float currentTemp = 0;
float previousTemp = 0;

char * deviceName = "NAMN";// <----------------------------------------------------
char * ssid = "Gurka";
char * pass = "gintonic";
char * connection = "LÄGG IN DIN SPECIELLA NYCKEL HÄR.iot.eu-north-1.amazonaws.com"; // <----------------------------------------------------
char postNord[100];

RH_ASK driver(2000, 4, 5, 0);
WiFiClientSecure espClient = WiFiClientSecure();
PubSubClient client(espClient);
