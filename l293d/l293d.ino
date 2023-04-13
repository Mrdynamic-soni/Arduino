#include <AFMotor.h> 
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
void setup() {

  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4f.setSpeed(200);

  // put your setup code here, to run once:

}
void loop() { 
motor1.run(FORWARD);       
delay(1000); 
motor2.run(FORWARD);       
delay(1000); 
motor3.run(FORWARD);       
delay(1000); 
motor4.run(FORWARD);       
delay(1000); 

motor1.run(BACKWARD);       
delay(1000); 
motor2.run(BACKWARD);       
delay(1000); 
motor3.run(BACKWARD);       
delay(1000); 
motor4.run(BACKWARD);       
delay(1000);   
motor1.run(RELEASE);       
delay(1000); 
motor2.run(RELEASE);       
delay(1000); 
motor3.run(RELEASE);       
delay(1000); 
motor4.run(RELEASE);       
delay(1000);   
}
