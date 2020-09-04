#include <Arduino.h>
#include <string>
#include <NTPClient.h>
#include <WiFiUdp.h>


String retornoHoraData();
void log(String texto);
long calculoSegundo(String arg);