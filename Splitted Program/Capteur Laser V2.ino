/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

int cote = 1;
VL53L0X sensorA;
VL53L0X sensorB;
VL53L0X sensorC;

void setup()
{  


  Serial.begin(9600);
  Wire.begin();

if (cote == 1) {


  sensorA.init();
  sensorA.setTimeout(500);
  sensorA.setAddress(29);
  sensorA.startContinuous();
  delay(200);
  Serial.print("Adresse du capteur 1: ");
  Serial.println(sensorA.getAddress());
  

  sensorB.init();
  sensorB.setTimeout(500);
  sensorB.setAddress(28);
  sensorB.startContinuous();
  delay(200);
  Serial.print("Adresse du capteur 2: ");
  Serial.println(sensorB.getAddress()); }
  
if (cote == 0) {
  sensorC.init();
  sensorC.setTimeout(500);
  sensorC.setAddress(27);
  sensorC.startContinuous();
  delay(200);
  Serial.print("Adresse du capteur 3: ");
  Serial.println(sensorC.getAddress()); }
  

}

void loop()
{

  if (cote == 1) {
Serial.print("Capteur du haut:   ");
    Serial.print(sensorA.readRangeContinuousMillimeters());
  if (sensorA.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  delay(10);

Serial.print("               Capteur du bas:   ");
    Serial.println(sensorB.readRangeContinuousMillimeters());
  if (sensorB.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
delay(10);  }

if (cote == 0){
Serial.print("               Capteur du Milieu:   ");
    Serial.println(sensorC.readRangeContinuousMillimeters());
  if (sensorC.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
delay(10); 
  
}







  
}
