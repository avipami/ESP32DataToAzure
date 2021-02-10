
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

char* ssid = "Gurka";
char* pass = "gintonic";
char* conn = "HostName=vinniesEmpire.azure-devices.net;SharedAccessKeyName=device;SharedAccessKey=TYLk0ZPuBEXZct2GlqQuPzBEEsC/NKLaTK+gd3bP3RA=";

bool messagePending = false;
bool messageSending = true;

IOTHUB_CLIENT_LL_HANDLE deviceClient;
