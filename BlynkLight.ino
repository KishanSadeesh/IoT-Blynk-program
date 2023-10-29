#define BLYNK_TEMPLATE_ID "TMPL3NSsVxxfC"
#define BLYNK_TEMPLATE_NAME "lightonoff"
#define BLYNK_AUTH_TOKEN "Zsgbf7C-pwTBvc7YY5uPg00AJwgBzdUG"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "Zsgbf7C-pwTBvc7YY5uPg00AJwgBzdUG";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

#define LED 21
int SW_state = 0; 

BLYNK_WRITE (V1)
{
  SW_state = param.asInt();
  if(SW_state == 1){
    digitalWrite(LED, HIGH);
    Serial.println("LED on");
    Blynk.virtualWrite(V1, HIGH);
  }else{
    digitalWrite(LED, LOW);
    Serial.println("LED OFF");
    Blynk.virtualWrite(V1, LOW);
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
}
