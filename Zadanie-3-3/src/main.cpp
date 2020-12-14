#include <Arduino.h>

#define ADC_RESOLUTION_DEFAULT (5.0f / 1024.0f)

uint16_t digital;
float voltage;
void setup() {
  Serial.begin(9600);
 analogReference(DEFAULT);
 pinMode(A0, INPUT);
}

void loop(){
  digital = analogRead(A0);
  voltage = ADC_RESOLUTION_DEFAULT * digital;
  Serial.print("A0 = ");
  Serial.print(digital);
  Serial.print(" \t V(0) = ");
  Serial.print(voltage);
  Serial.println(" [V]");
  delay(1000);
}