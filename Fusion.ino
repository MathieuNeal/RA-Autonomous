int emp;



/// PIN KIKO ///
#include <Wire.h>
#include <VL53L0X.h>
int cote = 1;  // SI COTE = 0, alors le coté est le gauche, si COTE = 1, le coté est le droit
float medium;
float sensorc;
float sensorc2;
float sensorc3;
float sensorc4;

VL53L0X sensor;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;




/// PIN BOOST ///
int motorPin1 = 40;                                       //Motorpin 1 sera branché sur la broche 40 de la mega
int motorPin2 = 41;                                       //Motorpin 2 sera branché sur la broche 41 de la mega
int motorPin3 = 42;                                       //Motorpin 3 sera branché sur la broche 42 de la mega
int motorPin4 = 43;                                      //Motorpin 4 sera branché sur la broche 43 de la mega
int ENA=11;   
int ENB=12;
int Av = 1;
int Ar = 2;
int St = 3;
int Tu = 4;
int state = 10;
const int fourchePin = 13;
const int ledPin =  9;
int EtatFourche = 0 ;
int CMPFOURCHE1 = 0; 


/// PIN THEO///
// Capteur 1
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 32;    // Broche ECHO
// Capteur 2
const byte TRIGGER_PIN2 = 3; // Broche TRIGGER
const byte ECHO_PIN2 = 33;    // Broche ECHO
// Capteur 3
const byte TRIGGER_PIN3 = 4; // Broche TRIGGER
const byte ECHO_PIN3 = 34;    // Broche ECHO
// Capteur 4 
const byte TRIGGER_PIN4 = 5; // Broche TRIGGER
const byte ECHO_PIN4 = 35;    // Broche ECHO
const byte timetostart = 10;
/// définition des constantes.Pas besoin de définir ça pour chacun (le timeout / vitesse du son ne change pas) 
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000;
const byte DEL = 11;

///
void setup() {
  Serial.begin(115200);
  emp = 0;
  
// SETUP KIKO //
   medium = 0;

  pinMode(46, OUTPUT); // CAPTEUR GAUCHE AVANT
  pinMode(47, OUTPUT); // CAPTEUR GAUCHE ARRIERE
 // pinMode(7, OUTPUT); // LED DE TEST
 // pinMode(8, OUTPUT); // LED DE TEST
  pinMode(48, OUTPUT); // CAPTEUR DROITE AVANT
  pinMode(49, OUTPUT);// CAPTEUR DROITE ARRIERE
  // Mettre les XSHUT à 0 pour ne pas griller la carte
  digitalWrite(46, LOW);
  digitalWrite(47, LOW);
  digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  delay(5);
  Wire.begin();
  
 initcapteur();
  
  
  
  
  // SETUP THEO // 
  pinMode(DEL,OUTPUT);
   // on indique quelle pin sert à quoi pour chaque capteur
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); 
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  digitalWrite(TRIGGER_PIN2, LOW); 
  pinMode(ECHO_PIN2, INPUT);
    pinMode(TRIGGER_PIN3, OUTPUT);
  digitalWrite(TRIGGER_PIN3, LOW); 
  pinMode(ECHO_PIN3, INPUT);
    pinMode(TRIGGER_PIN4, OUTPUT);
  digitalWrite(TRIGGER_PIN4, LOW);
  pinMode(ECHO_PIN4, INPUT);
//

// SETUP BOOST // 
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
pinMode(ledPin, OUTPUT);     //LED en sortie
pinMode(fourchePin, INPUT);  //en entrée
Serial.println("Fourche optique - detection de presence");
//



}

void loop() {


if(emp == 0){
digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);
analogWrite(ENA,60);
analogWrite(ENB,60); 
mesureultrason1();

mesureultrason2();

mesureultrason3();

mesureultrason4();

capteurlaser(); }



  delay(timetostart); // voir "timetostart" au début. permet de définir le nb de milliseconde avant que le programme se relance }


              }






  void turnleft()
  {
digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);


analogWrite(ENA,60);
analogWrite(ENB,60);
delay(50);
  }


 void turnright(){
  digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, HIGH);


analogWrite(ENA,60);
analogWrite(ENB,60);
delay(50);
 }

void stopmotor() {
digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, HIGH);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
}


 void initcapteur() {
    //SENSOR
  pinMode(46, INPUT);
  delay(150);
 Serial.println("Get adress of sensor 1");   /// Récupérer l'adresse du capteur 1 en I2C
  sensor.init(true);
 Serial.println("Init of the sensor 1 ");    
  delay(100);
  sensor.setAddress((uint8_t)22);


  //SENSOR 2
  pinMode(47, INPUT);
  delay(150);
  sensor2.init(true);
Serial.println("Get adress of sensor 2");  /// Récupérer l'adresse du capteur 2 en I2C
  delay(100);
  sensor2.setAddress((uint8_t)25);
Serial.println("Init of the sensor 2"); 

  //SENSOR 3
  pinMode(48, INPUT);
  delay(150);
  sensor3.init(true);
Serial.println("Get adress of sensor 3");  /// Récupérer l'adresse du capteur 3 en I2C
  delay(100);
  sensor3.setAddress((uint8_t)26);
 Serial.println("Init of the sensor 3"); 

   //SENSOR 4
  pinMode(49, INPUT);
  delay(150);
  sensor4.init(true);
Serial.println("Get adress of sensor 4");  /// Récupérer l'adresse du capteur 4 en I2C
  delay(100);
  sensor4.setAddress((uint8_t)27);
  Serial.println("Init of the sensor 4"); 
 


  sensor.setTimeout(200);
  sensor2.setTimeout(200);
  sensor3.setTimeout(200);
  sensor4.setTimeout(200);
 }


void mesureultrason1() {

    digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);


  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  
  Serial.print(F("Distance Capteur 1 : "));
  Serial.print(distance_mm);
  Serial.print (F("mm (")); // pas de "println" comme ça on met tout les capteurs sur la même ligne

if( distance_mm < 51 && distance_mm > 1) { ///////////////////// CAPTEUR 1 à -50mm)

/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm < 51 && distance_mm > 1) {
Serial.println("VERIFICATION DU CAPTEUR 1 : A 5CM DU MUR");
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
                        }               }

  
        }


void mesureultrason2() {



    digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  
  long measure2 = pulseIn(ECHO_PIN2, HIGH, MEASURE_TIMEOUT); //// Normalement, une fois que la mesure du capteur 1 est bonne, on devrait pouvoir réutiliser la variable "measure" et "distance_mm". mais c'est plus facile d'en faire une autre. puis ça aidera au debuggage
  float distance_mm2 = measure2 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 2 : "));
  Serial.print(distance_mm2);
  Serial.print(F("mm (")); // Toujours pas de println. 


 if( distance_mm2 < 51 && distance_mm2 > 1) /////////////////////////// CAPTEUR 2 à -50mm)
{ 
/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  long measure = pulseIn(ECHO_PIN2, HIGH, MEASURE_TIMEOUT);
  float distance_mm2 = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//

if (distance_mm2 < 51 && distance_mm2 > 1) {
Serial.println("VERIFICATION DU CAPTEUR 2 : a 5 CM");
analogWrite(DEL,255);
// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  long measure = pulseIn(ECHO_PIN2, HIGH, MEASURE_TIMEOUT);
  float distance_mm2 = measure / 2.0 * SOUND_SPEED;
                                          } 

                }
}





void mesureultrason3() {
    digitalWrite(TRIGGER_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN3, LOW);
  
  long measure3 = pulseIn(ECHO_PIN3, HIGH, MEASURE_TIMEOUT);
  float distance_mm3 = measure3 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 3 : "));
  Serial.print(distance_mm3);
  Serial.print(F("mm (")); 



 if( distance_mm3 < 75 && distance_mm3 > 1) { /// CAPTEUR 1 à -50mm)
/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN3, LOW);
  long measure = pulseIn(ECHO_PIN3, HIGH, MEASURE_TIMEOUT);
  float distance_mm3 = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm3 < 75) {
Serial.println("VERIFICATION DU CAPTEUR 3 :ARRET MOTEUR");

stopmotor();

analogWrite(DEL,255);}  }
}





void mesureultrason4()
{
  
  digitalWrite(TRIGGER_PIN4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN4, LOW);
  
  long measure4 = pulseIn(ECHO_PIN4, HIGH, MEASURE_TIMEOUT);
  float distance_mm4 = measure4 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 4 : "));
  Serial.print(distance_mm4);
  Serial.println(F("mm ("));  /// et là on met enfin le println


 if( distance_mm4 < 75 && distance_mm4 > 1) { //////////////// CAPTEUR 4 à -75mm)
/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN4, LOW);
  long measure = pulseIn(ECHO_PIN4, HIGH, MEASURE_TIMEOUT);
  float distance_mm4 = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm4 < 75 && distance_mm4 > 1) {
Serial.println("VERIFICATION DU CAPTEUR 4 :ARRET MOTEUR");

stopmotor();
  
analogWrite(DEL,255);

digitalWrite(TRIGGER_PIN4, HIGH); /// ON REFAIT LA MESURE
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN4, LOW);
  long measure = pulseIn(ECHO_PIN4, HIGH, MEASURE_TIMEOUT);
  float distance_mm4 = measure / 2.0 * SOUND_SPEED;
  
                        }                 }
      }



void capteurlaser() {

if(cote != 1) {

    Serial.print("Gauche Avant   (mm):  ");
    Serial.print( sensor.readRangeSingleMillimeters() );
sensorc = sensor.readRangeSingleMillimeters();

   Serial.print("      "); // Pour mettre de l'espace entre les 2 affichages de distance sans toucher au serial.print "Distance 2..."
    Serial.print("Gauche Arriere   (mm): ");
    Serial.print(sensor2.readRangeSingleMillimeters());
    Serial.println(""); 
sensorc2 = sensor2.readRangeSingleMillimeters();


    medium = sensorc / sensorc2;
        if(medium > 1.05 && medium < 8160)
                       {  
                      turnleft();
                        }

    if(0.95 > medium && medium > 1)
                        {
                        turnright();    
                         }
    
                        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(cote != 0) {
   Serial.print("      "); // Pour mettre de l'espace entre les 2 affichages de distance sans toucher au serial.print "Distance 2..."
    Serial.print("Droite Avant   (mm): ");
    Serial.print(sensor3.readRangeSingleMillimeters());
    Serial.print("");
 sensorc3 = sensor3.readRangeSingleMillimeters();

   Serial.print("      "); // Pour mettre de l'espace entre les 2 affichages de distance sans toucher au serial.print "Distance 2..."
    Serial.print("Droite arriere   (mm): ");
    Serial.print(sensor4.readRangeSingleMillimeters());
    Serial.println("");
 sensorc4 = sensor4.readRangeSingleMillimeters();

    medium = sensorc3 / sensorc4;

    if(medium > 1.05 && medium < 8160)
                       {  
                      turnleft();
                        }

    if(0.95 > medium && medium > 1)
                        {
                        turnright();    
                         }
      
             }




 
 // delay(timetostart); 
  } 


  
void emp() {
  
}





