
#include <Servo.h>
Servo myservo;  
Servo myservo2;
int pos;
int pastservo=0;

int cote;
int lastetat; 
int cmpfourche=0;


int ledPin = 13;                // choose the pin for the LED
int inputPin = 3;   
int emp = 0;
// Connect sensor to input pin 3 
int motorPin1 = 40;                                       //Motorpin 1 sera branché sur la broche 40 de la mega
int motorPin2 = 41;                                       //Motorpin 2 sera branché sur la broche 41 de la mega
int motorPin3 = 42;                                       //Motorpin 3 sera branché sur la broche 42 de la mega
int motorPin4 = 43;                                      //Motorpin 4 sera branché sur la broche 43 de la mega
int ENA=11;   
int ENB=12;

int state = 10;
const int fourchePin = 8;
int EtatFourche = 0 ;
int CMPFOURCHE1 = 0; 



/Cale (FOURCHE OPTIQUE)
int cale = 36;

void setup() {
pastservo=0;
emp = 0;

pinMode(A5, INPUT_PULLUP);

  myservo2.attach(10); 

  myservo.attach(9);

pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
 Serial.begin(230400);
  Serial.println("Initialisation");
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare pushbutton as input

    delay(1000); 
  Serial.println("On abaisse le bras");
  myservo.write(175);
  
   delay(1000); 
int cote = digitalRead(A5); // DEFINIR SENS DU SWITCH


///////////////////

while(digitalRead (cale) != 0) {
  digitalWrite(13, HIGH);
  delay(20);
  digitalWrite(13,LOW); }

//////////////////
}

void loop(){




if (pastservo != 1){
//  delay(2000); 
//  Serial.println("On abaisse le bras");
  myservo.write(175);
}



  
  int val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {       
   pastservo=1;
    myservo.write(90);
  digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, HIGH);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);


 if (cote != 1) { turnright(); Serial.println("TOURNE A GAUCHE"); }
 if (cote == 1) { turnleft(); Serial.println("TOURNE A DROITE"); }

    
    delay(2000);
 digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);
analogWrite(ENA,60);
analogWrite(ENB,60); 
emp = 1;
Serial.println("Emp changé");
  /// ON APPUIE 
  } else {

//  ON APPUIE PAS

  digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, HIGH);
analogWrite(ENA,60);
analogWrite(ENB,60); 
 


if (emp != 0) {
  
  EtatFourche = digitalRead(fourchePin);
  if(EtatFourche == 1 && EtatFourche != lastetat) { cmpfourche = cmpfourche+1;  Serial.println("+1");  }

   
Serial.print("          CMP: ");
Serial.println(cmpfourche);
while( cmpfourche > 40){
 Serial.println("Mission accomplie");



digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, HIGH);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);

 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);            // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

}
   
              }


lastetat = EtatFourche;
  } // FIN DU BOUTON
  
}


void turnleft(){
digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW); 
digitalWrite(motorPin4, HIGH);


analogWrite(ENA,60);
analogWrite(ENB,60);
delay(50);
}


void turnright() {
    digitalWrite(motorPin1, LOW); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);


analogWrite(ENA,60);
analogWrite(ENB,60);
delay(50);
}
