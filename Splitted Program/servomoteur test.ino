
#include <Servo.h>
int pos;
Servo myservo2;
void setup() {
  // put your setup code here, to run once:

  myservo2.attach(9); 

  delay(5000);
}

void loop() {
   for (pos = 90; pos <= 170; pos += 1) { 
  
    myservo2.write(pos);              
    delay(5);                       
  }

  
  for (pos = 170; pos >= 90; pos -= 1) { 
    myservo2.write(pos);          
delay(5); 
}





}
