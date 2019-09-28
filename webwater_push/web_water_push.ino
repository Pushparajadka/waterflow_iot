#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Initialize.h"
int temp;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(A0, INPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);


}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (Serial.available() > 0)
  {
    int water1 = Serial.parseInt();
    int water2 = Serial.parseInt();
    int water3 = Serial.parseInt();
    int water4 = Serial.parseInt();
    int water5 = Serial.parseInt();
    //    Serial.print(water1);
    //    Serial.print('|');
    //    Serial.print(water2);
    //    Serial.print('|');
    //    Serial.print(water3);
    //    Serial.print('|');
    //    Serial.print(water4);
    //    Serial.print('|');
    //    Serial.println(water5);


    char stemp[10],s1[10],s2[10],s3[10],s4[10];
    //    char  *stemp = char(temp);
    itoa(water1, stemp, 10);
    itoa(water2, s1, 10);
    itoa(water3, s2, 10);
    itoa(water4, s3, 10);
    itoa(water5, s4, 10);
    //String stemp = temp + '\0';
    Serial.println(water1);
    //Serial.println(stemp);
    //client.publish("Temp1", "2");
    if (((water1) > 0) || ((water2) > 0) || ((water3) > 0) || ((water4) > 0) || ((water5) > 0))
    {
      client.publish("water1", stemp);
      client.publish("water2", s1);
      client.publish("water3", s2);
      client.publish("water4", s3);
      client.publish("water5", s4);
      //client.publish("Temp1", "I am RK once again");
      Serial.println("pubilshed");
      delay(100);
    }
    //delay(1000);

  }
}
