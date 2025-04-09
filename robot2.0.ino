#define ULTRASONIC_SENSOR_TRIG 11
#define ULTRASONIC_SENSOR_ECHO 12

#define MAX_FORWARD_MOTOR_SPEED 75
#define MAX_MOTOR_TURN_SPEED_ADJUSTMENT 100

#define MIN_DISTANCE 10
#define MAX_DISTANCE 30

#define IR_SENSOR_RIGHT 3
#define IR_SENSOR_LEFT 2

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed);
long duration; 
int distance; 

// Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 9;
int rightMotorPin2 = 10;

// Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 8;
int leftMotorPin2 = 7;

void setup() {
  pinMode(ULTRASONIC_SENSOR_TRIG, OUTPUT); 
  pinMode(ULTRASONIC_SENSOR_ECHO, INPUT); 
  delay(500);

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0, 0);   
}

void loop() {
  digitalWrite(ULTRASONIC_SENSOR_TRIG, LOW);
  delayMicroseconds(2); 
  digitalWrite(ULTRASONIC_SENSOR_TRIG, HIGH);
  delayMicroseconds(2); 
  digitalWrite(ULTRASONIC_SENSOR_TRIG, LOW); 
  duration = pulseIn(ULTRASONIC_SENSOR_ECHO, HIGH);
  distance = duration * (0.0340 / 2); 
  delay(10); // Reduced delay for better responsiveness

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  // Logic for motor control
  if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
      rotateMotor(0,100); 
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
      rotateMotor(100,0); 
  }
  else if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
    rotateMotor(MAX_FORWARD_MOTOR_SPEED, MAX_FORWARD_MOTOR_SPEED);
  }
  else if (distance == MIN_DISTANCE) {
    rotateMotor(0,0);
    delay(1000);
  }
  else if (distance < MIN_DISTANCE) {
    rotateMotor(-MAX_FORWARD_MOTOR_SPEED, -MAX_FORWARD_MOTOR_SPEED);
    delay(30);
  }
  //  else if (distance <= MIN_DISTANCE && distance >= MAX_DISTANCE) {
  //   rotateMotor(0, 0);
  // }
  // else if(rightIRSensorValue == HIGH && leftIRSensorValue == HIGH) {
  //   rotateMotor(MAX_FORWARD_MOTOR_SPEED, MAX_FORWARD_MOTOR_SPEED);
  // }
  //  else {
  //   rotateMotor(MAX_FORWARD_MOTOR_SPEED, MAX_FORWARD_MOTOR_SPEED);
  // // }
  else {
    rotateMotor(0, 0);
  }
}  // <-- Added closing brace for loop()
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
    if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  }
  else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);      
  }
  else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);      
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);    
  }
  else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);      
  }
  else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
 abs(leftMotorSpeed);    
}