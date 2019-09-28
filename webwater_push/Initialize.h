#include <PubSubClient.h>
#include <ESP8266WiFi.h>
const char* ssid = "free net";  
const char* password = "hello123";
const char* mqtt_server = "www.mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client1(espClient);
int i;
char msg[10];

bool setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(">>");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}
void reconnect() {
  // Loop until we're reconnected
  while (!client1.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    if (client1.connect(" clientId-ZABPsNnECg", "iotnode", "iotnode!")) // clientID,username,password
    {
      Serial.println("connected:-)");
      // Once connected, publish an announcement...
      //client.publish("Temp1", "I am TNK");
      //client.publish("Temp2", "I am RK");
      // ... and resubscribe
      client1.subscribe("Temp1");
      client1.subscribe("MC1_on");
      client1.subscribe("MC1_off");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    delay(100);
     msg[i] = (char)payload[i];
  }
  Serial.println();
}

