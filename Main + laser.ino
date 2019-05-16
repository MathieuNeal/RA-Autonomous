//____________________________________________________________________________________________
//  PROGRAMME DU ROBOT AUTONOME TROPHEES DE ROBOTIQUE
//
//                  2019 - ATOM FACTORY
//
//  PROJET SIN 2018-2019 : JOLY Quentin, BERGA Florian, DANIELE Théo
//
//---------------------------------------------------------------------------------------------
//
//  VERSION : V2 MARION
//
//  MODIFICATIONS : METTRE 2 VITESSES DE ROTATION DIFFERENTES POUR LES MOTEURS AFIN DE REGLER UN DEPLACEMENT LINEAIRE SANS DERIVE
//                   INTEGRATION DES CAPTEURS POUR PARAMETRER LES DEPLACEMENTS
//                  Cabler les capteurs à fourche sur des pins avec interruptions externes :  pin2(int ext 0), pin3(int ext 1), pin18(int ext 5), pin19(int ext 4), pin20(int ext 3), pin21(int ext 2)
//
//  CARACTERISTIQUES : DIAMETRE DES ROUES    : 65 mm A MESURER
//                     NB DE TROUS ENCODEURS : 22 ou 24 A VERIFIER
//                     RAPPORT REDUCTION     : 1/48 (pas besoin car le codeur est placé après le reducteur) A VERIFIER
//
//_____________________________________________________________________________________________

//*********************************************************************************************
// Insertion des bibliothèques
//*********************************************************************************************
#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
//*********************************************************************************************
// DEFINITION DES ALIAS
//*********************************************************************************************
#define POS_HAUTE_SERVO_EXPERIENCE  80    // angle en degré de la position haute du servo
#define POS_BASSE_SERVO_EXPERIENCE  170   // angle en degré de la position basse du servo

#define VITESSE_MOTEURS       100    // valeur de la PWM des 2 moteurs à changer pour ralentir ou accélérer le robot
#define VITESSE_MOTEUR_GAUCHE 100    // valeur de la PWM du moteur GAUCHE
#define VITESSE_MOTEUR_DROIT  100    // valeur de la PWM du moteur DROIT

#define DIAMETRE_ROUE     65   // valeur en mm du diamètre des roues
#define RAPPORT_REDUCTION 1    // Valeur du rapport de réduction ici 1 car par de reducteur
#define NB_TROUS_ENCODEUR 22   // valeur du nombre de trous sur l'encodeur

#define CALE_ENLEVEE    HIGH
#define CALE_PRESENTE   LOW
#define COTE_ORANGE     LOW
#define COTE_VIOLET     HIGH
#define BUMPER_ENFONCE  HIGH
#define BUMPER_LIBRE    LOW 
#define VRAI            HIGH
#define FAUX            LOW
#define ORANGE          0
#define VIOLET          1

//*********************************************************************************************
// DEFINTION DES PINS SUR LA MEGA
//*********************************************************************************************
// Ponts en H des moteurs
#define PIN_SENS1_MOT_DROIT   40  //Sens 1 Moteur DROIT (pont en H): IN1 sera branché sur la broche 40 de la mega 
#define PIN_SENS2_MOT_DROIT   41  //Sens 2 Moteur DROIT (pont en H): IN2 sera branché sur la broche 41 de la mega 
#define PIN_PWM_MOT_DROIT     11  //PWM Moteur DROIT  : ENA sera branché sur la broche 11 de la mega 
#define PIN_SENS1_MOT_GAUCHE  42  //Sens 1 Moteur GAUCHE (pont en H): IN3 sera branché sur la broche 42 de la mega 
#define PIN_SENS2_MOT_GAUCHE  43  //Sens 2 Moteur GAUCHE (pont en H): IN4 sera branché sur la broche 43 de la mega
#define PIN_PWM_MOT_GAUCHE    12  //PWM Moteur GAUCHE : ENB sera branché sur la broche 12 de la mega 
// ----------------------------
// capteurs à fourches placés au niveau des moteurs Gauche et Droit pour mesurer les déplacements et la vitesse de rotation
// Choisir des pins avec interruptions externes, sur la mega : 2, 3, 18, 19, 20, ou 21
#define PIN_COMPTEUR_MOT_GAUCHE 18  // encodeur moteur GAUCHE pin 18 : interruption externe 5
#define PIN_COMPTEUR_MOT_DROIT  19  // encodeur moteur DROIT  pin 19 : interruption externe 4
// ----------------------------
// Servomoteurs
#define PIN_SERVO_EXPERIENCE    9 //Motorpin 1 sera branché sur la broche 40 de la mega 
//#define PIN_SERVO_ACCELERATEUR  10  //Motorpin 2 sera branché sur la broche 41 de la mega 
// ----------------------------
// Capteur à fourche pour déclencher le départ du robot autonome avec la cale à ficelle
#define PIN_CALE_DEPART   36  //CALE sera branché sur la broche 36 de la mega
// ----------------------------
// Bumper avant
#define PIN_BUMPER_AV   3 // bouton poussoir à l'avant branché sur la broche 3 de la Méga
// ----------------------------
// Interrupteur de coté JAUNE ou VIOLET
#define PIN_INTERRUPTEUR_COTE   5 // l'interrupteur pour indiquer le coté de départ est connecté à la beoche 5 de la Méga
// ----------------------------
// Pin des capteurs lasers XSHUT
#define PIN_XSHUT_AVG 46
#define PIN_XSHUT_ARG 47
#define PIN_XSHUT_AVD 48
#define PIN_XSHUT_ARD 49

// Adresses I2C des capteurs lasers
#define Addresse_Capteur_laser_AVG 29
#define Addresse_Capteur_laser_ARG 30
#define Addresse_Capteur_laser_AVD 31
#define Addresse_Capteur_laser_ARD 32
// SCA est connecté  à la broche 20 de la Méga fil BLEU
// SCL est connecté  à la broche 21 de la Méga fil VERT
// ----------------------------
// capteurs à ultra sons pour détecter les obstacles
#define PIN_ULTRASON_TRIGGER_AV   2  // TRIGGER Ultrason AVANT (DROITE) est connecté à la broche 2 de la Méga
#define PIN_ULTRASON_ECHO_AV      4  // ECHO Ultrason AVANT (DROITE) est connecté à la broche 4 de la Méga
#define PIN_ULTRASON_TRIGGER_AR   6  // TRIGGER Ultrason ARRIERE (GAUCHE) est connecté à la broche 6 de la Méga
#define PIN_ULTRASON_ECHO_AR      7  // ECHO Ultrason ARRIERE (GAUCHE) est connecté à la broche 7 de la Méga
// ----------------------------

//*********************************************************************************************
// DECLARATION DES VARIABLES GLOBALES
//*********************************************************************************************
int couleur_depart;

// Définition des Capteurs laser 

VL53L0X Capteur_laser_AVG;
VL53L0X Capteur_laser_ARG;
VL53L0X Capteur_laser_AVD;
VL53L0X Capteur_laser_ARD;

// Définition des servomoteurs
Servo servo_experience;     // servo de l'expérience
//Servo servo_accelerateur;   // servo de l'atome dans l'accélérateur
// variable permettant d'effectuer le cycle de déplacement qu'une seule fois dans le programme principal (loop)
int fin_du_cycle;

float AVD;
float ARD;
float AVG;
float ARG;

float calculdroite; 
float calculgauche;
//*********************************************************************************************
// Fonction SETUP
//*********************************************************************************************
void setup()
{ 

Serial.begin(115200);
Wire.begin();

    // capteurs Laser pour longer les murs
  init_laser(); 
  // Déclaration de la broche utilisée par le servo de l'expérience
  servo_experience.attach(PIN_SERVO_EXPERIENCE);
  
  // Déclaration de la broche utilisée par le servo de l'expérience
  //servo_accelerateur.attach(PIN_SERVO_ACCELERATEUR);

  //-------------------------------------------------------------------------------------------
  // Configuration en Entrée ou en Sortie des broches de la MEGA
  // pont en H
  pinMode(PIN_SENS1_MOT_DROIT, OUTPUT);   // IN1 en sortie : ecriture sur le port
  pinMode(PIN_PWM_MOT_DROIT, OUTPUT);     // ENA en sortie : ecriture sur le port
  pinMode(PIN_SENS1_MOT_GAUCHE, OUTPUT);  // IN3 en sortie : ecriture sur le port
  pinMode(PIN_SENS2_MOT_GAUCHE, OUTPUT);  // IN4 en sortie : ecriture sur le port
  pinMode(PIN_PWM_MOT_GAUCHE, OUTPUT);    // ENB en sortie : ecriture sur le port
  // Capteur à fourche pour déclencher le départ du robot autonome avec la cale à ficelle
  pinMode(PIN_CALE_DEPART, INPUT);        // Capteur à fourche déclenchement départ, lecture : en entrée
  // Bumper avant
  pinMode(PIN_BUMPER_AV, INPUT);          // Bumper avant, lecture : en entrée
  // Interrupteur de coté JAUNE ou VIOLET
  pinMode(PIN_INTERRUPTEUR_COTE, INPUT);  // interrupteur coté JAUNE ou VIOLET, lecture : en entrée
  

  // capteurs à ultra sons pour détecter les obstacles
  pinMode(PIN_ULTRASON_TRIGGER_AV, OUTPUT); // TRIGGER Ultrason AVANT (DROITE) en sortie : ecriture sur le port
  pinMode(PIN_ULTRASON_ECHO_AV, INPUT);     // ECHO Ultrason AVANT (DROITE) en entrée : lecture sur le port
  pinMode(PIN_ULTRASON_TRIGGER_AR, OUTPUT); // TRIGGER Ultrason ARRIERE (GAUCHE) en sortie : ecriture sur le port
  pinMode(PIN_ULTRASON_ECHO_AR, INPUT);     // ECHO Ultrason ARRIERE (GAUCHE) en entrée : lecture sur le port
  // Interrupteur pour choisir le coté
  pinMode(PIN_INTERRUPTEUR_COTE, INPUT);
  //-------------------------------------------------------------------------------------------

  // initialisation de la variable fin de cycle à FAUX
  // car le cycle de déplacement ne s'est pas encore effectué
  fin_du_cycle = FAUX;
  
 
Serial.print("Etat du bouton");
Serial.println(digitalRead(PIN_INTERRUPTEUR_COTE));
delay(200);
 


} // fin du SETUP

void loop() {


//  Serial.print("distance AVG = "); Serial.print(Capteur_laser_AVG.readRangeSingleMillimeters());
//  Serial.print(" - distance ARG = "); Serial.print(Capteur_laser_ARG.readRangeSingleMillimeters());

if (digitalRead(PIN_CALE_DEPART) == CALE_ENLEVEE && fin_du_cycle == FAUX)
  { 
    mesure_laser(); 
  
delay(200);
  }





}
//---------------------------------------------------------------------------------------------------------------
// DEFINITION DES FONCTIONS
//---------------------------------------------------------------------------------------------------------------
void attente_ms(unsigned long temps_attente_ms) 
{ 
  delay(temps_attente_ms);
} 
//----------------------------------------------------------------
void arret_robot() 
{ 
  digitalWrite(PIN_SENS1_MOT_GAUCHE, HIGH);
  digitalWrite(PIN_SENS2_MOT_GAUCHE, HIGH);
  digitalWrite(PIN_SENS1_MOT_DROIT, HIGH);
  digitalWrite(PIN_SENS2_MOT_DROIT, HIGH); 
  digitalWrite(PIN_PWM_MOT_GAUCHE,LOW); 
  digitalWrite(PIN_PWM_MOT_DROIT,LOW); ; 
} 
void marche_avant()
{
  
  digitalWrite(PIN_SENS1_MOT_GAUCHE, LOW); 
  digitalWrite(PIN_SENS2_MOT_GAUCHE, HIGH); 
  digitalWrite(PIN_SENS1_MOT_DROIT, LOW); 
  digitalWrite(PIN_SENS2_MOT_DROIT, HIGH); 
  analogWrite(PIN_PWM_MOT_GAUCHE,VITESSE_MOTEURS); 
  analogWrite(PIN_PWM_MOT_DROIT,VITESSE_MOTEURS); 
}
void marche_arriere()
{
  digitalWrite(PIN_SENS1_MOT_GAUCHE, HIGH);
  digitalWrite(PIN_SENS2_MOT_GAUCHE, LOW);
  digitalWrite(PIN_SENS1_MOT_DROIT, HIGH);
  digitalWrite(PIN_SENS2_MOT_DROIT, LOW);
  analogWrite(PIN_PWM_MOT_GAUCHE, VITESSE_MOTEURS);
  analogWrite(PIN_PWM_MOT_DROIT, VITESSE_MOTEURS); ; 
}
void rotation_gauche()
{ 
  digitalWrite(PIN_SENS1_MOT_GAUCHE, HIGH); 
  digitalWrite(PIN_SENS2_MOT_GAUCHE, LOW); 
  digitalWrite(PIN_SENS1_MOT_DROIT, LOW); 
  digitalWrite(PIN_SENS2_MOT_DROIT, HIGH); 
  analogWrite(PIN_PWM_MOT_GAUCHE,VITESSE_MOTEUR_GAUCHE); 
  analogWrite(PIN_PWM_MOT_DROIT,VITESSE_MOTEUR_DROIT); 
  delay(50);
} 
void rotation_droite()
{
  digitalWrite(PIN_SENS1_MOT_GAUCHE, LOW);
  digitalWrite(PIN_SENS2_MOT_GAUCHE, HIGH);
  digitalWrite(PIN_SENS1_MOT_DROIT, HIGH);
  digitalWrite(PIN_SENS2_MOT_DROIT, LOW);
  analogWrite(PIN_PWM_MOT_GAUCHE,VITESSE_MOTEUR_GAUCHE);
  analogWrite(PIN_PWM_MOT_DROIT,VITESSE_MOTEUR_DROIT);
  delay(50);
}
//----------------------------------------------------------------
void init_laser(){/*WARNING*/
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  //pinMode(PIN_XSHUT_AVG, OUTPUT);
  pinMode(PIN_XSHUT_ARG, OUTPUT);
  pinMode(PIN_XSHUT_AVD, OUTPUT);
  pinMode(PIN_XSHUT_ARD, OUTPUT);

  Capteur_laser_AVG.init();
  Capteur_laser_AVG.setTimeout(500);
  Capteur_laser_AVG.setAddress(Addresse_Capteur_laser_AVG);
  //Capteur_laser_AVG.startContinuous();
  delay(200);
  Serial.print("Adresse Capteur_laser_AVG : "); Serial.print(Capteur_laser_AVG.getAddress()); Serial.println();

  pinMode(PIN_XSHUT_ARG, INPUT);
  Capteur_laser_ARG.init();
  Capteur_laser_ARG.setTimeout(500);
  Capteur_laser_ARG.setAddress(Addresse_Capteur_laser_ARG);
  //Capteur_laser_ARG.startContinuous();
  delay(200);
  Serial.print("Adresse Capteur_laser_ARG : "); Serial.print(Capteur_laser_ARG.getAddress()); Serial.println();

  pinMode(PIN_XSHUT_AVD, INPUT);
  Capteur_laser_AVD.init();
  Capteur_laser_AVD.setTimeout(500);
  Capteur_laser_AVD.setAddress(Addresse_Capteur_laser_AVD);
  //Capteur_laser_AVD.startContinuous();
  delay(200);
  Serial.print("Adresse Capteur_laser_AVD : "); Serial.print(Capteur_laser_AVD.getAddress()); Serial.println();

  pinMode(PIN_XSHUT_ARD, INPUT);
  Capteur_laser_ARD.init();
  Capteur_laser_ARD.setTimeout(500);
  Capteur_laser_ARD.setAddress(Addresse_Capteur_laser_ARD);
  //Capteur_laser_ARD.startContinuous();
  delay(200);
  Serial.print("Adresse Capteur_laser_ARD : "); Serial.print(Capteur_laser_ARD.getAddress()); Serial.println();
}


void mesure_laser(){


    if (digitalRead(PIN_INTERRUPTEUR_COTE) == 0) {
AVD = Capteur_laser_AVD.readRangeSingleMillimeters();
ARD = Capteur_laser_ARD.readRangeSingleMillimeters(); 
  Serial.print(" - distance AVD = "); Serial.print(AVD);
  Serial.print(" - distance ARD = "); Serial.print(ARD);
 calculdroite = AVD / ARD; 
  Serial.println("            Moyenne:  ");
 Serial.println(calculdroite); 
  }


  if (digitalRead(PIN_INTERRUPTEUR_COTE) == 1) {
AVG = Capteur_laser_AVG.readRangeSingleMillimeters(); 
ARG = Capteur_laser_ARG.readRangeSingleMillimeters();
  Serial.print(" - distance AVG = "); Serial.print(AVG);
  Serial.print(" - distance ARG = "); Serial.print(ARG);
 calculgauche = AVG / ARG;
  Serial.println("            Moyenne:  ");
  Serial.println(calculgauche); 
  }  


}
//----------------------------------------------------------------
void bras_experience_releve()
{
  servo_experience.write(POS_HAUTE_SERVO_EXPERIENCE);
}
void bras_experience_abaisse(){
  servo_experience.write(POS_BASSE_SERVO_EXPERIENCE);
}
//-------------------------------------------------------------------------------------------------
