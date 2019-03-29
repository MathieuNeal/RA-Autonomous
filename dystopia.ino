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
int Av = 1;
int Ar = 2;
int St = 3;
int Tu = 4;
int state = 10;
const int fourchePin = 8;
int EtatFourche = 0 ;
int CMPFOURCHE1 = 0; 

void setup() {


emp = 0;

pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
Serial.begin(9600);
  Serial.println("Initialisation");
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare pushbutton as input
}

void loop(){





  
  int val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {       
   
    
  digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, HIGH);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
    
    delay(2000);
 digitalWrite(motorPin1, HIGH); 
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH); 
digitalWrite(motorPin4, LOW);
analogWrite(ENA,60);
analogWrite(ENB,60); 
delay(3000);
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
    digitalWrite(ledPin, HIGH); // turn LED ON


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

}
   
              }


lastetat = EtatFourche;
  }






  
}
