#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const int button = 5;
const int duration = 8000;
const int LED = 4;


void setup() {

  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  
  Serial.begin(115200);
  delay(4000);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ssid", "pw");
  Serial.print("Lets Go \n");
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    digitalWrite(LED,HIGH);
    if (!digitalRead(button)){
      digitalWrite(LED,LOW);
      Serial.print("Butten Pressed \n");
      send("http://192.168.178.97/win&&PL=2");
      delay(duration);
      send("http://192.168.178.97/win&&PL=1");
      Serial.print("Animation done \n");
    }   
  }
}

void send(String msg){
  WiFiClient client;
  HTTPClient http;
  //Serial.print("[HTTP] begin...\n"); 
  if (http.begin(client, msg)) {
    Serial.print("sending request \n");
    int httpCode = http.GET();
    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
    }
}
