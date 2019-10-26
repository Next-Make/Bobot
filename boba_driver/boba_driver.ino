#include <config.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(MILK_TO_TEA, OUTPUT);
  pinMode(TEA_TO_BOBA, OUTPUT);
  pinmode(WATER_TO_TEA, OUTPUT);
  pinMode(WATER_TO_BOBA, OUTPUT);
  pinMode(BOBA_TO_WASTE, OUTPUT);
  pinMode(TEABAG_MOTOR, OUTPUT);
  pinmode(TEA_TEMP_SENSOR, INPUT);
  pinmode(BOBA_TEMP_SENSOR, INPUT);
  pinmode(TEA_HEATER, OUTPUT);
  pinmode(BOBA_HEATER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
