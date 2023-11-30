/**
 ******************************************************************************
   @file        aula_wifi.ino
   @author      Airton Toyofuku
   @copyright   None
   @date        25.08.2023
   @version     1.0
   @brief       Arduino Sketch
 ******************************************************************************
*/
/* Private includes ----------------------------------------------------------*/
#include "Arduino.h"
#include "WiFi.h"             // WiFi Library
#include "DHT.h"
#include <HTTPClient.h>

/* Private Defines -----------------------------------------------------------*/
#define APP_NAME    "IoT Tago+Wifi"
#define APP_VERSION "1.0.0"
#define SEPARATOR_LINE "****************************************************"

/* WiFi Configuration---------------------------------------------------------*/
char wifiSsid[] = "iPhone Airton"; // This is the WiFi network name!
char wifiPass[] = "2153818aa";     // This is the wifi password!

/* Tago Configuration----------------------------------------------------------*/
char serverAddress[] = "https://api.tago.io/data";  // TagoIO address
char contentHeader[] = "application/json";
char tokenHeader[]   = "39655860-2b75-4730-a4c4-eca18d30d189"; // TagoIO Token

HTTPClient client;
int dhtHumidity;
int  dhtTemperature;
/**
   @brief Setup Function
*/
void setup() {
  // put your setup code here, to run once:
  // Setting the Console Serial Communication
  Serial.begin(9600);
  Serial.println(SEPARATOR_LINE);
  Serial.print(APP_NAME );
  Serial.print("_");
  Serial.println(APP_VERSION);
  Serial.println(SEPARATOR_LINE);

  // Init the wifi connection
  init_wifi();
}

/**
   @brief Infinit Loop Function
*/
void loop() {
  // put your main code here, to run repeatedly:
  //dhtHumidity++;
  //dhtTemperature++;

  dhtTemperature = dht.readTemperature();
  dhtHumidity = dht.readHumidity();
  
  send_temperature();
  send_humidity();
  delay(5000);
}

/**
   @brief Initializes the wifi connection
*/
void init_wifi(void) {
  Serial.println("Conectando Wifi...");
  Serial.print("SSID: ");
  Serial.println(wifiSsid);
  Serial.print("PASS: ");
  Serial.println(wifiPass);

  WiFi.begin(wifiSsid, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Conectado!");
  Serial.print("IP is ");
  Serial.println(WiFi.localIP());
}

/**
   @brief Send temperature to tago
*/
void send_temperature(void){
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"Temperature\",\n\t\"value\": ");
  dtostrf(dhtTemperature, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);

  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  delay(2000);

  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

/**
   @brief Sends Humidity data to tago
*/
void send_humidity(void) {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;


  strcpy(postData, "{\n\t\"variable\": \"Humidity\",\n\t\"value\": ");
  dtostrf(dhtHumidity, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);

  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  delay(5000);

  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}