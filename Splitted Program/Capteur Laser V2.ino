/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>


VL53L0X sensorA;
VL53L0X sensorB;
void setup()
{  pinMode(5, OUTPUT);


  Serial.begin(9600);
  Wire.begin();

digitalWrite(5, LOW);
  sensorA.init();
  sensorA.setTimeout(500);
  sensorA.setAddress(29);
  sensorA.startContinuous();
  delay(200);
  Serial.print("Adresse du capteur 1: ");
  Serial.println(sensorA.getAddress());
  
digitalWrite(5, HIGH);
  sensorB.init();
  sensorB.setTimeout(500);
  sensorB.setAddress(28);
  sensorB.startContinuous();
  delay(200);
  Serial.print("Adresse du capteur 2: ");
  Serial.println(sensorB.getAddress());

}

void loop()
{
Serial.print("Capteur du haut:   ");
    Serial.print(sensorA.readRangeContinuousMillimeters());
  if (sensorA.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  delay(10);

Serial.print("               Capteur du bas:   ");
pinMode(5, INPUT);
    Serial.println(sensorB.readRangeContinuousMillimeters());
  if (sensorB.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
delay(10);
}
