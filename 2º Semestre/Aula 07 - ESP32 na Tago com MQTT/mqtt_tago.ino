#include <ArduinoJson.h>    // Lib to format JSON Document
#include "EspMQTTClient.h"  // Lib to comunicate MQTT from ESP

//Doc: https://github.com/plapointe6/EspMQTTClient

char  temperaturaJson[100];
float valorTemperatura = 0;

//MQTT and WiFi configuration
EspMQTTClient client
(
  "WiFI",                //nome da sua rede Wi-Fi
  "2153818aa",           //senha da sua rede Wi-Fi
  "mqtt.tago.io",       //Endereço do servidor MQTT
  "Default",            //User é sempre default pois vamos usar token
  "TOKEN",              // Código do Token
  "esp32",              //Nome do device
  1883                  //Porta de comunicação padrao
);

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Conectando WiFi");
  while(!client.isWifiConnected()){
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("Conectado!");

  Serial.println("Conectando com o broker MQTT");
  while(!client.isMqttConnected()){
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("Conectado!");
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{}

//loop do programa
void loop()
{
  //Getting temperature and Humidity data
  valorTemperatura++;

  StaticJsonDocument<300> documentoJson;
  documentoJson["variable"] = "temperatura";
  documentoJson["value"] = valorTemperatura;
  serializeJson(documentoJson, temperaturaJson);
  Serial.println("Enviando dados de temperatura");
  Serial.println(temperaturaJson);
  
  client.publish("topicTemperatura", temperaturaJson); 
  delay(5000);

  client.loop();
}