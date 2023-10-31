#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"



#define led 18


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "Kishan1403"
#define AIO_KEY         "aio_bUgu61UeH2NNyuvSPSstfH3uaCLu"

WiFiClient client;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");


Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led, OUTPUT);
  Serial.println(F("Adafruit MQTT demo"));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to Wifi......");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  
  Serial.println(); 
  Serial.println();
  
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  
  mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {

  MQTT_connect();


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      uint16_t state= atoi((char *)onoffbutton.lastread);
      digitalWrite(led, state);
    }
  }

 
}

void MQTT_connect() {
  int8_t ret;

 
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  
       retries--;
       if (retries == 0) {
         
        while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
