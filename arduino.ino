// Motor control pins (2 motors, one for movement and one for turning)
int motorPinLeftA = 2;  // Left motor direction A
int motorPinLeftB = 3;  // Left motor direction B
int motorPinLeftPWM = 5;  // Left motor PWM control for speed

int motorPinRightA = 4;  // Right motor direction A
int motorPinRightB = 7;  // Right motor direction B
int motorPinRightPWM = 6;  // Right motor PWM control for speed

// Array to store moves with a maximum of 100 moves
String moves[100];
int moveIndex = 0;

// Ultrasonic sensor pins (3 sensors)
#define trigPin0 11  // Trig pin for sensor 1 (front)
#define echoPin0 12  // Echo pin for sensor 1 (front)

#define trigPin1 A0  // Trig pin for sensor 2 (left)
#define echoPin1 A1  // Echo pin for sensor 2 (left)

#define trigPin2 A2  // Trig pin for sensor 3 (right)
#define echoPin2 A3  // Echo pin for sensor 3 (right)

void setup() {
  Serial.begin(9600);

  // Motor control pins setup (2 motors for movement)
  pinMode(motorPinLeftA, OUTPUT);
  pinMode(motorPinLeftB, OUTPUT);
  pinMode(motorPinLeftPWM, OUTPUT);  // PWM pin for left motor speed

  pinMode(motorPinRightA, OUTPUT);
  pinMode(motorPinRightB, OUTPUT);
  pinMode(motorPinRightPWM, OUTPUT);  // PWM pin for right motor speed

  // Ultrasonic sensor pins setup
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  long duration0, distance0;
  long duration1, distance1;
  long duration2, distance2;

  // Trigger sensor 0 (front)
  digitalWrite(trigPin0, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin0, LOW);
  duration0 = pulseIn(echoPin0, HIGH);
  distance0 = (duration0 / 2) / 29.1;
  Serial.print("front left: ");
  Serial.print(distance0);
  Serial.println("");

  // Trigger sensor 1 (left)
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  Serial.print("middle: ");
  Serial.print(distance1);
  Serial.println("");

  // Trigger sensor 2 (right)
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;
  Serial.print("front right: ");
  Serial.print(distance2);
  Serial.println("");

  // Obstacle avoidance logic
  if (distance0 < 20 || distance1 < 20 || distance2 < 20) {
    stopMotors();
    delay(100);

    if (distance1 < 20) {
      turnRight();
      recordMove("turnRight");
    } else if (distance2 < 20) {
      turnLeft();
      recordMove("turnLeft");
    } else {
      turnRight();
      recordMove("turnLeft");
    }
  } else {
    moveForward();
    recordMove("moveForward");
  }

  delay(100);
}

// Function to record moves
void recordMove(String move) {
  if (moveIndex < 100) {  // Ensure we don’t exceed array bounds
    moves[moveIndex] = move;
    moveIndex++;
  }
}

// Motor functions for 2 motors

void moveForward() {
  // Move the left motor forward with PWM for speed control
  digitalWrite(motorPinLeftA, LOW);
  digitalWrite(motorPinLeftB, HIGH);
  analogWrite(motorPinLeftPWM, 200);  // Set speed to 50% (128 out of 255)

  // Move the right motor forward with PWM for speed control
  digitalWrite(motorPinRightA, LOW);
  digitalWrite(motorPinRightB, HIGH);
  analogWrite(motorPinRightPWM, 200);  // Set speed to 50% (128 out of 255)

  Serial.println("Moving forward");
}

void stopMotors() {
  // Stop the left motor
  digitalWrite(motorPinLeftA, LOW);
  digitalWrite(motorPinLeftB, LOW);
  analogWrite(motorPinLeftPWM, 0);  // Stop the motor

  // Stop the right motor
  digitalWrite(motorPinRightA, LOW);
  digitalWrite(motorPinRightB, LOW);
  analogWrite(motorPinRightPWM, 0);  // Stop the motor

  Serial.println("Motors stopped");
}

void turnLeft() {
  // Turn the left motor backward with PWM for speed control
  digitalWrite(motorPinLeftA, LOW);
  digitalWrite(motorPinLeftB, HIGH);
  analogWrite(motorPinLeftPWM, 200);  // Set speed to 50%

  // Turn the right motor forward with PWM for speed control
  digitalWrite(motorPinRightA, HIGH);
  digitalWrite(motorPinRightB, LOW);
  analogWrite(motorPinRightPWM, 200);  // Set speed to 50%

  Serial.println("Turning left");
}

void turnRight() {
  // Turn the left motor forward with PWM for speed control
  digitalWrite(motorPinLeftA, HIGH);
  digitalWrite(motorPinLeftB, LOW);
  analogWrite(motorPinLeftPWM, 200);  // Set speed to 50%

  // Turn the right motor backward with PWM for speed control
  digitalWrite(motorPinRightA, LOW);
  digitalWrite(motorPinRightB, HIGH);
  analogWrite(motorPinRightPWM, 200);  // Set speed to 50%

  Serial.println("Turning right");
}

// Function to return to the starting position
void returnToStart() {
  Serial.println("Returning to start...");

  // Rotate 180 degrees to face the starting direction
  turnLeft();
  delay(2000);  // Time for 180-degree rotation
  stopMotors();
  delay(500);

  // Execute recorded moves in reverse order
  for (int i = moveIndex - 1; i >= 0; i--) {
    String move = moves[i];
    if (move == "moveForward") {
      moveForward();
      delay(100);
    } else if (move == "turnLeft") {
      turnRight();
      delay(100);
    } else if (move == "turnRight") {
      turnLeft();
      delay(100);
    }
    stopMotors();
    delay(500);
  }
  Serial.println("Returned to start.");
}
