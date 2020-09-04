#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Thread.h>
#include <ArduinoJson.h>
#include "utis.h"




String ssid = "Mariano_2G";
String password = "20061977";
String id = "0";
String idRetorno = "";
String idIot = "0";
String nameIot = "teste";
String tipoIot = "IOT";
String nomeConector = "teste";
String atualEstado = "ON";
//String server = "34.69.67.128";
//String server = "2001:1284:f013:b957:e911:cd0d:2220:24b0";
String server = "192.168.0.103";
String jSon = "";
int porta = 27015;
String usuario = "Matinhos";
String senha = "M@r0403";
int status = WL_IDLE_STATUS;
int interruptor = LOW;
int hora = 0;
int minuto = 0;
int segundo = 0;
int dia = 0;
int mes = 0;
int ano = 0;
boolean conectado = false;
boolean aliveRetorno = false;
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3 * 3600, 60000);
String horaAtual;
String horaAtualResetar;
boolean horaAtualResetarInicializar = false;
boolean acionarTemporizador = false;
boolean aguardandoTemporizador = false;
long horaInicioTemporizador;
long horaFinalTemporizador;
boolean ativarAleatorio = false;
int ultimoAcionador = 2;

int minutoAletorio;
String horaTemporizador;
String minutoAtual;
String segundoAtual;
String dataHora ;
long duracao;

String mostradorRelogio = "";
StaticJsonDocument<1000> doc;
StaticJsonDocument<1000> com;
Thread myThread = Thread();
WiFiClient client;
//String retornoHoraData();
void inicializaTemporizador();
void log(String texto);
String alive();
bool bLigarPiscina = true;
bool bdesLigarPiscina = false;
bool foraHorarioTimer = false;