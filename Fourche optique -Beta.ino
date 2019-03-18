const int fourchePin = 13;
const int ledPin =  9; // pas utilisé ici 
int cmpfourche;
int EtatFourche = 0 ;
int lastetat;
// Initialisation



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
void setup() {
  Serial.begin(115200);   //connection au port série
  pinMode(ledPin, OUTPUT);     //LED en sortie
  pinMode(fourchePin, INPUT);  //en entrée
  Serial.println("Fourche optique - detection de presence");



pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);

delay(100);

digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);
analogWrite(ENA,60);
analogWrite(ENB,60); 

}

void loop() {



  Serial.print("EF:");
  EtatFourche = digitalRead(fourchePin);
Serial.print (EtatFourche);

if(EtatFourche == 1 && EtatFourche != lastetat) { cmpfourche = cmpfourche+1;    }
Serial.print("                                                CMP");
Serial.println(cmpfourche);


if( cmpfourche > 15) {Serial.println("UN TOUR"); // cmpfourche = 0;   
 
digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, HIGH);
 
 }



lastetat = EtatFourche;

}
