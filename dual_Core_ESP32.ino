#include "DHT.h"
#define DHTPIN 27
#define DHTTYPE DHT11 
const int led = 2;  
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200); 
  pinMode(led, OUTPUT);
dht.begin();
xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL,  1); 
  delay(500); 
xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL,  0); 
    delay(500); 
}
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
  } 
}
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
      float h = dht.readHumidity();
    float t = dht.readTemperature();
     float f = dht.readTemperature(true);
      Serial.print("Temperature: ");
     Serial.print(t);
   Serial.print(" *C \n ");
     if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    delay(2000);
  }
}
void loop() {
}
