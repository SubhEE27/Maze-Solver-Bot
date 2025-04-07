#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial espSerial(A0, A1);
String receivedData = "";
float receivedFloat = 0.0; // Variable to store received data

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
    Serial.begin(9600);        // Debugging on Serial Monitor
    espSerial.begin(9600);

    // motor1.setSpeed(200);
    // motor2.setSpeed(200);
    // motor3.setSpeed(200);
    // motor4.setSpeed(200);
    
    // motor1.run(RELEASE);
    // motor2.run(RELEASE);
    // motor3.run(RELEASE);
    // motor4.run(RELEASE);
}

void loop() {
  if (espSerial.available() >= sizeof(float)) {
        float receivedFloat;
        espSerial.readBytes((char*)&receivedFloat, sizeof(receivedFloat));

        Serial.print("Received from ESP32: ");
        Serial.println(receivedFloat, 2);  // Print received float with 2 decimal places
    }
}
