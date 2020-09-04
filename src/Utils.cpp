#include "utis.h"


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3 * 3600, 60000);
bool timeBegin = false;


String retornoHoraData() {
    if (!timeBegin){
        timeClient.begin();
        timeBegin = true;
    }
    timeClient.update();
    return timeClient.getFormattedTime();
}

void log(String texto) {
  Serial.println(retornoHoraData() + " " + texto);
}

long calculoSegundo(String arg) {
  return arg.substring(0, 2).toInt() * 3600 + arg.substring(3, 5).toInt() * 60 + arg.substring(6, 8).toInt();
}