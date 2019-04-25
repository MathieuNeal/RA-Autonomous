//____________________________________________________________________________________________
//  PROGRAMME DU ROBOT AUTONOME TROPHEES DE ROBOTIQUE
//
//                  2019 - ATOM FACTORY
//
//  PROJET SIN 2018-2019 : JOLY Quentin, BERGA Florian, DANIELE Théo
//
//---------------------------------------------------------------------------------------------
//
//  VERSION : MARION V1
//
//  MODIFICATIONS : RE ORGANISATION DU CODE PROG V3 (avant expérience arrière) POUR UNE MEILLEURE LISIBILITE DU PROGRAMME
//  PROGRAMME MARCHE AVANT PUIS RECUL
//  AJOUT DU DEBUT POUR FAIRE L'ACCELERATEUR DE PARTICULES
//_____________________________________________________________________________________________

//*********************************************************************************************
// Insertion des bibliothèques
//*********************************************************************************************
#include <Servo.h>

//*********************************************************************************************
// DEFINITION DES ALIAS
//*********************************************************************************************
#define POS_HAUTE_SERVO_EXPERIENCE	90		// angle en degré de la position haute du servo
#define POS_BASSE_SERVO_EXPERIENCE	170		// angle en degré de la position basse du servo

#define CALE_ENLEVEE	LOW
#define CALE_PRESENTE	HIGH
#define COTE_JAUNE		LOW
#define COTE_VIOLET		HIGH
#define BUMPER_ENFONCE HIGH
#define BUMPER_LIBRE	LOW	
#define VRAI			    HIGH
#define FAUX			    LOW

//*********************************************************************************************
// DEFINTION DES PINS SUR LA MEGA
//*********************************************************************************************
// Ponts en H des moteurs
#define MOTORPIN1		40	//Motorpin 1 sera branché sur la broche 40 de la mega 
#define MOTORPIN2		41	//Motorpin 2 sera branché sur la broche 41 de la mega 
#define MOTORPIN3		42	//Motorpin 3 sera branché sur la broche 42 de la mega 
#define MOTORPIN4		43	//Motorpin 4 sera branché sur la broche 43 de la mega
#define PIN_ENA			11	//ENA sera branché sur la broche 11 de la mega 
#define PIN_ENB			12	//ENB sera branché sur la broche 12 de la mega 
//#define PIN_STATE		10	//STATE sera branché sur la broche 43 de la mega 
// Servomoteurs
#define PIN_SERVO_EXPERIENCE	9	//Motorpin 1 sera branché sur la broche 40 de la mega 
//#define PIN_SERVO_ACCELERATEUR	10	//Motorpin 2 sera branché sur la broche 41 de la mega 
// Capteur à fourche pour déclencher le départ du robot autonome avec la cale à ficelle
#define PIN_CALE		36	//CALE sera branché sur la broche 36 de la mega
// Interrupteur de coté JAUNE ou VIOLET
#define PIN_INTER_COTE	5
// Bumper avant
#define PIN_BUMPER	3	// bouton poussoir à l'avant branché sur la broche 3 de la Méga


//*********************************************************************************************
// DECLARATION DES VARIABLES GLOBALES
//*********************************************************************************************
// Définition des servomoteurs
Servo servo_experience;     // servo de l'expérience
//Servo servo_accelerateur;   // servo de l'atome dans l'accélérateur


//*********************************************************************************************
// Fonction SETUP
//*********************************************************************************************
void setup()
{ 
  // Déclaration de la broche utilisée par le servo de l'expérience
  servo_experience.attach(PIN_SERVO_EXPERIENCE);
  
  // Déclaration de la broche utilisée par le servo de l'expérience
  //servo_accelerateur.attach(PIN_SERVO_ACCELERATEUR);
  
  // Configuration en Entrée ou en Sortie des broches de la MEGA
  pinMode(PIN_ENA, OUTPUT);		// pont en H
  pinMode(PIN_ENB, OUTPUT);		// pont en H
  pinMode(MOTORPIN1, OUTPUT);	// pont en H 
  pinMode(MOTORPIN2, OUTPUT);	// pont en H 
  pinMode(MOTORPIN3, OUTPUT);	// pont en H 
  pinMode(MOTORPIN4, OUTPUT);	// pont en H
  pinMode(PIN_INTER_COTE, INPUT);	// interrupteur coté JAUNE ou VIOLET, lecture : en entrée
  pinMode(PIN_BUMPER, INPUT);		// Bumper avant, lecture : en entrée
  pinMode(PIN_CALE, INPUT);			// Capteur à fourche déclenchement départ, lecture : en entrée
  
  // Les moteurs sont à l'arrêt
  arret_robot();
  // Le bras du déclenchement de l'expéreince est en position haute
  bras_experience_releve();  
} 

//*********************************************************************************************
// PROGRAMME PRINCIPAL
//*********************************************************************************************
void loop()
{ 
  // variable permettant d'effectuer le cycle de déplacement qu'une seule fois dans le programme principal (loop)
  int fin_du_cycle = FAUX;

  // variable permettant de stocker le côté de départ du robot : JAUNE ou VIOLET
  int cote_depart;
  
  // si la cale de départ est enlevée du capteur à fourche on demarre la séquence du robot autonome
	// la variable fin_du_cycle permet d'exécuter qu'une seuke fois la séquence de déplacement
	if (digitalRead(PIN_CALE) == CALE_ENLEVEE && fin_du_cycle == FAUX)
	{
		// on lit la position de l'interrupteur pour savoir de quel côté est le robot autonome : JAUNE ou VIOLET
		cote_depart = digitalRead(PIN_INTER_COTE);

    //********************************
		// DEPLACEMENT VERS l'EXPERIENCE
		//********************************
		// On baisse le bras du déclenchement de l'expéreince
		bras_experience_abaisse();  
		// Le robot se déplace en marche avant vers l'expérience tant que le bumper avant n'est pas en contact avec le bord de la table
		do { marche_avant(); }
		while(digitalRead(PIN_BUMPER) == BUMPER_LIBRE);
		// on arrète les moteurs, dès que le bumper avant est en contatc avec le bord de la table, 
		arret_robot();
		// L'expérience est réalisée, on relève le bras
		bras_experience_releve();
		// atente de 0,5s avant de reculer
		delay(500);	
		// puis on repart en arrière pendant 1s
		marche_arriere();
		delay(1000);
		// et on arrête le robot
		arret_robot();
		
		//***********************************************
    // DEPLACEMENT VERS l'ACCELERATEUR DE PARTICULE
    //***********************************************
		// si le robot autonome est du coté JAUNE
		if (cote_depart == COTE_JAUNE)
		{
			// coté JAUNE 
		}
		
		// si le robot autonome est du coté VIOLET 
		if (cote_depart == COTE_VIOLET)
		{
			// coté VIOLET 
		}
		
		// c'est la fin du cycle, le déplacement doit s'effectuer 1 seule fois 
		fin_du_cycle = VRAI;
	}
} 
// FIN DU PROGRAMMLE PRINCIPAL


//---------------------------------------------------------------------------------------------------------------
// DEFINITION DES FONCTIONS
//---------------------------------------------------------------------------------------------------------------
void arret_robot() 
{ 
	digitalWrite(MOTORPIN1, HIGH);
	digitalWrite(MOTORPIN2, HIGH);
	digitalWrite(MOTORPIN3, HIGH);
	digitalWrite(MOTORPIN4, HIGH); 
  digitalWrite(PIN_ENA,LOW); 
  digitalWrite(PIN_ENB,LOW); 
} 
void marche_avant()
{
	digitalWrite(MOTORPIN1, LOW); 
  digitalWrite(MOTORPIN2, HIGH); 
  digitalWrite(MOTORPIN3, LOW); 
  digitalWrite(MOTORPIN4, HIGH); 
  analogWrite(PIN_ENA,100); 
  analogWrite(PIN_ENB,100); 
}
void marche_arriere()
{
  digitalWrite(MOTORPIN1, HIGH);
  digitalWrite(MOTORPIN2, LOW);
  digitalWrite(MOTORPIN3, HIGH);
  digitalWrite(MOTORPIN4, LOW);
  analogWrite(PIN_ENA, 100);
  analogWrite(PIN_ENB, 100); 
}
void rotation_gauche()
{ 
  digitalWrite(MOTORPIN1, HIGH); 
  digitalWrite(MOTORPIN2, LOW); 
  digitalWrite(MOTORPIN3, LOW); 
  digitalWrite(MOTORPIN4, HIGH); 
  analogWrite(PIN_ENA,100); 
  analogWrite(PIN_ENB,100); 
  delay(50);
} 
void rotation_droite()
{
	digitalWrite(MOTORPIN1, LOW);
	digitalWrite(MOTORPIN2, HIGH);
	digitalWrite(MOTORPIN3, HIGH);
	digitalWrite(MOTORPIN4, LOW);
	analogWrite(PIN_ENA,100);
	analogWrite(PIN_ENB,100);
	delay(50);
}
//----------------------------------------------------------------
void bras_experience_releve()
{
	servo_experience.write(POS_HAUTE_SERVO_EXPERIENCE);
}
void bras_experience_abaisse()
{
	servo_experience.write(POS_BASSE_SERVO_EXPERIENCE);
}
//-------------------------------------------------------------------------------------------------
