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
// SETUP THEO // 

  Serial.begin(115200);
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
  // put your main code here, to run repeatedly:




state = Serial.parseInt();


/*
EtatFourche = digitalRead(fourchePin);
if (EtatFourche < 40) {  
EtatFourche=EtatFourche ++;
Serial.println(EtatFourche);  
} 
if (EtatFourche = 40) {
digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, LOW); 
} */


if (state == Av){Serial.println("Avant");

digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);
analogWrite(ENA,60);
analogWrite(ENB,60); }                                     

if (state == Ar){Serial.println("Arriere");

digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, HIGH);

analogWrite(ENA,60);
analogWrite(ENB,60); }

if (state == St){Serial.println("Stop"); 

digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, LOW);}

if (state == Tu) {Serial.println("Turn");

digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);


analogWrite(ENA,60);
analogWrite(ENB,60);}






  ////////////// MESURE CAPTEUR 1 //////////
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);


  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  
  Serial.print(F("Distance Capteur 1 : "));
  Serial.print(distance_mm);
  Serial.print (F("mm (")); // pas de "println" comme ça on met tout les capteurs sur la même ligne



  /////////////MESURE CAPTEUR 2 /////// 

 
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  
  long measure2 = pulseIn(ECHO_PIN2, HIGH, MEASURE_TIMEOUT); //// Normalement, une fois que la mesure du capteur 1 est bonne, on devrait pouvoir réutiliser la variable "measure" et "distance_mm". mais c'est plus facile d'en faire une autre. puis ça aidera au debuggage
  float distance_mm2 = measure2 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 2 : "));
  Serial.print(distance_mm2);
  Serial.print(F("mm (")); // Toujours pas de println. 


/////////////////MESURE CAPTEUR 3 /////////


  digitalWrite(TRIGGER_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN3, LOW);
  
  long measure3 = pulseIn(ECHO_PIN3, HIGH, MEASURE_TIMEOUT);
  float distance_mm3 = measure3 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 3 : "));
  Serial.print(distance_mm3);
  Serial.print(F("mm (")); 


/////////////////MESURE CAPTEUR 4 /////////


  digitalWrite(TRIGGER_PIN4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN4, LOW);
  
  long measure4 = pulseIn(ECHO_PIN4, HIGH, MEASURE_TIMEOUT);
  float distance_mm4 = measure4 / 2.0 * SOUND_SPEED; 

  Serial.print(F("                Distance Capteur 4 : "));
  Serial.print(distance_mm4);
  Serial.println(F("mm ("));  /// et là on met enfin le println




if( distance_mm < 51 && distance_mm > 1) { /// CAPTEUR 1 à -50mm)

/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm < 51) {
Serial.println("VERIFICATION DU CAPTEUR 1 : A 5CM DU MUR");
}




 if( distance_mm2 < 51 && distance_mm2 > 1) { /// CAPTEUR 1 à -50mm)
/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  long measure = pulseIn(ECHO_PIN2, HIGH, MEASURE_TIMEOUT);
  float distance_mm2 = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm2 < 51) {
Serial.println("VERIFICATION DU CAPTEUR 2 : a 5 CM");
analogWrite(DEL,255);}  }
  


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

digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, LOW);

analogWrite(DEL,255);}  }


 if( distance_mm4 < 75 && distance_mm4 > 1) { /// CAPTEUR 1 à -50mm)
/// ON REFAIT LA MESURE ///
  digitalWrite(TRIGGER_PIN4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN4, LOW);
  long measure = pulseIn(ECHO_PIN4, HIGH, MEASURE_TIMEOUT);
  float distance_mm4 = measure / 2.0 * SOUND_SPEED;
/// MESURE FINIE ///
// on re-analyse la distance pour vérifier//
if (distance_mm4 < 75) {
Serial.println("VERIFICATION DU CAPTEUR 4 :ARRET MOTEUR");

digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, LOW);

analogWrite(DEL,255);}  }


  delay(timetostart); // voir "timetostart" au début. permet de définir le nb de milliseconde avant que le programme se relance
if(distance_mm > 51) {digitalWrite(DEL,LOW);}
if(distance_mm2 > 51) {digitalWrite(DEL,LOW);}
if(distance_mm3 > 75) {digitalWrite(DEL,LOW);}
if(distance_mm4 > 75) {digitalWrite(DEL,LOW);} }









}
