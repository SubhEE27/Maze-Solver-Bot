#include <AFMotor.h>

// Motor control setup
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int IR = A2;  // Sharp IR Sensor pin
int val = 0;
int rightTurn = 0;

// Struct to store movement history
struct Move {
  int x, y;
  char direction; // 'F' = Forward, 'R' = Right, 'L' = Left
};

// Stack for tracking movement history
Move moveStack[30]; 
int stackTop = -1;

// Array to store visited positions
int visited[8][8] = {0};  // Assuming a 8x8 maze (adjustable)

// Bot coordinates
int botX = 0, botY = 0;  // Start at start of the grid

void setup() {
  pinMode(IR, INPUT);
  Serial.begin(9600);

  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  visited[botX][botY] = 1; // Mark start position as visited
}

void loop() {
  val = analogRead(IR);
  Serial.println(val);
  delay(500);

  if (check() == 1) {  // Obstacle detected
    moveRight();
    pushMove(botX, botY, 'R');
    rightTurn++;
    delay(500);

    if (rightTurn == 1 && check() == 1) {
      moveLeft();
      delay(300);
      moveLeft();
      delay(300);

      if (check() == 1) { // Dead end detected
        Serial.println("Dead End! Initiating Backtracking...");
        backtrack();
      }
    }
    rightTurn = 0;
  } 
  else {
    if (!isVisited(botX, botY + 1)) {  // If forward is not visited
      moveForward();
      pushMove(botX, botY, 'F');
    } else {
      Serial.println("Forward path already visited, backtracking...");
      backtrack();
    }
  }
}

// Function to push movement to stack
void pushMove(int x, int y, char move) {
  if (stackTop < 49) {
    stackTop++;
    moveStack[stackTop] = {x, y, move};
    visited[x][y] = 1; // Mark this position as visited
  }
}

// Function to pop last movement
Move popMove() {
  if (stackTop >= 0) {
    return moveStack[stackTop--];
  }
  return {-1, -1, 'X'};  // Indicates an empty stack
}

// Function to check if a position is visited
bool isVisited(int x, int y) {
  return visited[x][y] == 1;
}

// Backtracking function
void backtrack() {
  while (stackTop >= 0) {
    Move lastMove = popMove();

    if (lastMove.direction == 'F') {
      moveBackward();
      delay(500);
    } 
    else if (lastMove.direction == 'R') {
      moveLeft();
      delay(500);
    } 
    else if (lastMove.direction == 'L') {
      moveRight();
      delay(500);
    }

    // If the path is open and unvisited, stop backtracking
    if (check() == 0 && !isVisited(botX, botY)) {
      Serial.println("Backtracked to new open path!");
      return;
    }
  }
}

// Move functions
void moveForward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  botY++; // Move forward increases Y coordinate
}

void moveBackward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  botY--; // Moving backward decreases Y coordinate
}

void moveRight() {
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor2.run(FORWARD);
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  motor3.run(FORWARD);
  delay(1000);
  botX++; // Right turn increases X coordinate
}

void moveLeft() {
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(1000);
  botX--; // Left turn decreases X coordinate
}

// Stops motors
void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Check for obstacle using Sharp IR sensor
int check() {
  if (val >= 560 && val <= 585) {
    Serial.println("Obstacle Detected");
    stopMotors();
    delay(200);
    return 1;  // Obstacle detected
  }
  return 0;  // No obstacle detected
}
