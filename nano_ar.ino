#include<AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int IR=A2;
int val=0;
int rightTurn=0;

void setup() {
  pinMode(IR,INPUT);
  Serial.begin(9600);

  motor1.setSpeed(115);
  motor2.setSpeed(50);
  motor3.setSpeed(50);
  motor4.setSpeed(115);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  val=analogRead(IR);
  Serial.println(val);
  delay(500);
  if(check() == 1){
    moveRight();
    rightTurn++;
    delay(1000);
    if(rightTurn == 1 && check() == 1){
      moveLeft();
      delay(1000);
      moveLeft();
      delay(1000);
      if(check()==1){
        moveLeft();
        delay(1000);
      }
      else{
        moveForward();
      }
    }
    else{
      moveForward();
    }
    rightTurn=0;
  }
  else{
    moveForward();
  }
}

void moveForward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

int moveLeft() {
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(480);

  return 1;  // Indicate the right turn was executed
}

void stopMotors(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveRight(){
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  delay(480);
}

int check() {
  int currentVal = analogRead(IR); // Read the sensor value again
  Serial.println(currentVal);
  
  if(currentVal >= 400 && currentVal <= 510) {
    stopMotors();
    delay(500);
    return 1; // Return 1 when an obstacle is detected
  }
  return 0; // Return 0 when no obstacle is detected
}
