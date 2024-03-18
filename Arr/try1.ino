#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#define LIMIT_SWITCH_PIN1 10
#define LIMIT_SWITCH_PIN2 9
#define LIMIT_SWITCH_PIN3 11
#define LIMIT_SWITCH_PIN4 A3

// Define the stepper motors and the pins the will use
AccelStepper stepperJ1(1, 3, 6);  // (Type:driver, STEP, DIR)
AccelStepper stepperJ2(1, 4, 7);
AccelStepper stepperJ3(1, 2, 5);
AccelStepper stepperJ4(1, 12, 13);

Servo gripperServo;

double x = 10.0;
double y = 10.0;
double L1 = 228;    // L1 = 228mm
double L2 = 136.5;  // L2 = 136.5mm
double theta1, theta2, phi, z;

int iter = 0;

int stepperJ1Position, stepperJ2Position, stepperJ3Position, stepper4Position;

const float theta1AngleToSteps = 44.444444;
const float theta2AngleToSteps = 35.555555;
const float phiAngleToSteps = 10;
const float zDistanceToSteps = 100;

void homing() {
  homeJ4();
  homeJ2();
  homeJ3();
  homeJ1();
}

void homeJ3() {
  pinMode(LIMIT_SWITCH_PIN3, INPUT_PULLUP);

  stepperJ3.setMaxSpeed(5000);
  stepperJ3.setAcceleration(1000);
  stepperJ3.setSpeed(1500);

  while (digitalRead(LIMIT_SWITCH_PIN3) == LOW) {
    stepperJ3.runSpeed();
    if (digitalRead(LIMIT_SWITCH_PIN3) == HIGH) break;
  }

  stepperJ3.setSpeed(-1000);
  stepperJ3.move(-8000);

  while (stepperJ3.distanceToGo() != 0) {
    stepperJ3.runToPosition();
  }
  // stepperJ3.runToPosition();
  stepperJ3.setCurrentPosition(0);
}

void homeJ1() { 
 //to maintain balance
  pinMode(LIMIT_SWITCH_PIN2, INPUT_PULLUP);
  stepperJ2.setMaxSpeed(5000);
  stepperJ2.setSpeed(1500);
  stepperJ2.moveTo(-4250);
  while (stepperJ2.distanceToGo() != 0) {
    stepperJ2.runToPosition();
  }

  pinMode(LIMIT_SWITCH_PIN1, INPUT_PULLUP);

  stepperJ1.setMaxSpeed(5000);
  stepperJ1.setAcceleration(2000);
  stepperJ1.setSpeed(1500);

  while (digitalRead(LIMIT_SWITCH_PIN1) == LOW) {
    stepperJ1.runSpeed();
    if (digitalRead(LIMIT_SWITCH_PIN1) == HIGH) break;
  }

  stepperJ1.setSpeed(-3000);
  stepperJ1.move(-8000);

  while (stepperJ1.distanceToGo() != 0) {
    stepperJ1.runToPosition();
    stepperJ1.setCurrentPosition(0);
  }

 //back to original position
  stepperJ2.setMaxSpeed(5000);
  stepperJ2.setSpeed(1500);
  stepperJ2.moveTo(0);
  while (stepperJ2.distanceToGo() != 0) {
    stepperJ2.runToPosition();
  }
}

void homeJ2() {
  pinMode(LIMIT_SWITCH_PIN2, INPUT_PULLUP);

  stepperJ2.setMaxSpeed(5000);
  stepperJ2.setAcceleration(2000);
  stepperJ2.setSpeed(1500);

  while (digitalRead(LIMIT_SWITCH_PIN2) == LOW) {
    stepperJ2.runSpeed();
    if (digitalRead(LIMIT_SWITCH_PIN2) == HIGH) break;
  }

  stepperJ2.setSpeed(-3000);
  stepperJ2.move(-5500);

  while (stepperJ2.distanceToGo() != 0) {
    stepperJ2.runToPosition();
    stepperJ2.setCurrentPosition(0);
  }

}

void homeJ4() {
  pinMode(LIMIT_SWITCH_PIN4, INPUT_PULLUP);

  stepperJ4.setMaxSpeed(5000);
  stepperJ4.setAcceleration(1000);
  stepperJ4.setSpeed(1500);

  while (digitalRead(LIMIT_SWITCH_PIN4) == LOW) {
    stepperJ4.runSpeed();
    if (digitalRead(LIMIT_SWITCH_PIN4) == HIGH) break;
  }

  stepperJ4.setSpeed(-3000);
  stepperJ4.move(-1500);

  while (stepperJ4.distanceToGo() != 0) {
    stepperJ4.runToPosition();
    stepperJ4.setCurrentPosition(0);
  }
}

// FORWARD KINEMATICS
void forwardKinematics() {
  float theta1F = theta1 * PI / 180;  // degrees to radians
  float theta2F = theta2 * PI / 180;
  int xP = round(L1 * cos(theta1F) + L2 * cos(theta1F + theta2F));  //For finding EE co-ordinates
  int yP = round(L1 * sin(theta1F) + L2 * sin(theta1F + theta2F));
  Serial.print("X :");
  Serial.println(xP);
  Serial.print("Y :");
  Serial.println(yP);
}

void arr(){
  int arr_theta1[4] = {90, -90, 50, -50};
  int arr_theta2[4]= {110, -110, 125, -125};
  float arr_z[4]= {0, 0, 0, 0};
  int arr_serAngle[4]= {0, 0, 0, 0};
}


void setup() {
  Serial.begin(9600);
  gripperServo.attach(A0, 600, 2500);
  gripperServo.write(0);           // tell servo to go to position in variable 'pos'                                                                   
  homing();

  for(int i = 0; i< 4; i++)
  {
    theta1 = arr_theta1[i];
    theta2 = arr_theta2[i];
    z = arr_z[i];
    serAngle = arr_serAngle[i];

    forwardKinematics();
    stepperJ1.setSpeed(4000);
    stepperJ2.setSpeed(4000);
    stepperJ3.setSpeed(4000);
    stepperJ1.setAcceleration(2000);
    stepperJ2.setAcceleration(2000);
    stepperJ3.setAcceleration(2000);

    //writing position to the steppers
    stepperJ1Position = theta1 * theta1AngleToSteps;
    stepperJ2Position = theta2 * theta2AngleToSteps;
    stepperJ3Position = Z * zDistanceToSteps;

    Serial.print("stepperJ1 steps taken :");
    Serial.println(stepperJ1Position);
    Serial.print("stepperJ2 steps taken :");
    Serial.println(stepperJ2Position);  
    Serial.print("stepperJ3 steps taken :");
    Serial.println(stepperJ3Position);
    Serial.print("Gripper position :");
    Serial.println(serAngle);

    Serial.print("Z :");
    Serial.println(Z);

    stepperJ1.moveTo(stepperJ1Position);
    stepperJ2.moveTo(stepperJ2Position);
    stepperJ3.moveTo(stepperJ3Position);

    if (serAngle == 0) {
    // in steps of 1 degree
      gripperServo.write(0);              // tell servo to go to position in variable 'pos'
      delay(15); 
      Serial.println("End Effector Closed");
    
    }
    else if (serAngle == 1) {
      gripperServo.write(90);              // tell servo to go to position in variable 'pos'
      delay(15);  
      Serial.println("End Effector Open");
    
    }

    while (stepperJ1.currentPosition() != stepperJ1Position || stepperJ2.currentPosition() != stepperJ2Position || stepperJ3.currentPosition() != stepperJ3Position) {
      stepperJ1.run();
      stepperJ2.run();
      stepperJ3.run();
    }
    delay(1000);
  }
}



void loop() {
  // Wait for input from the user
  if (Serial.available() > 0) {
    // Read the input from the user
    String input = Serial.readStringUntil('\n');

    // Parse the input into x, y, and z coordinates
    int comma1 = input.indexOf(",");
    int comma2 = input.indexOf(",", comma1 + 1);
    int comma3 = input.indexOf(",", comma2 + 1);
    int comma4 = input.indexOf(",", comma3 + 1);
    theta1 = input.substring(0, comma1).toFloat();           //Reads the first value entered in the string WHICH IS THETA 1
    theta2 = input.substring(comma1 + 1, comma2).toFloat();  //Reads the second value entered after the first comma WHICH IS THETA2
    float Z = input.substring(comma2 + 1).toFloat();         //Reads next value after the 2nd comma WHICH IS Z AXIS
    int serAngle = input.substring(comma3 + 1).toFloat();    //Reads next value after the 3rd comma


    //Calculate the forward kinamatics
    forwardKinematics();
    stepperJ1.setSpeed(4000);
    stepperJ2.setSpeed(4000);
    stepperJ3.setSpeed(4000);
    stepperJ1.setAcceleration(2000);
    stepperJ2.setAcceleration(2000);
    stepperJ3.setAcceleration(2000);

    //writing position to the steppers
    stepperJ1Position = theta1 * theta1AngleToSteps;
    stepperJ2Position = theta2 * theta2AngleToSteps;
    stepperJ3Position = Z * zDistanceToSteps;

    Serial.print("stepperJ1 steps taken :");
    Serial.println(stepperJ1Position);
    Serial.print("stepperJ2 steps taken :");
    Serial.println(stepperJ2Position);  
    Serial.print("stepperJ3 steps taken :");
    Serial.println(stepperJ3Position);
    Serial.print("Gripper position :");
    Serial.println(serAngle);

    Serial.print("Z :");
    Serial.println(Z);

    stepperJ1.moveTo(stepperJ1Position);
    stepperJ2.moveTo(stepperJ2Position);
    stepperJ3.moveTo(stepperJ3Position);

    if (serAngle == 0) {
    // in steps of 1 degree
      gripperServo.write(0);              // tell servo to go to position in variable 'pos'
      delay(15); 
      Serial.println("End Effector Closed");
    
    }
    else if (serAngle == 1) {
      gripperServo.write(90);              // tell servo to go to position in variable 'pos'
      delay(15);  
      Serial.println("End Effector Open");
    
    }

    while (stepperJ1.currentPosition() != stepperJ1Position || stepperJ2.currentPosition() != stepperJ2Position || stepperJ3.currentPosition() != stepperJ3Position) {
      stepperJ1.run();
      stepperJ2.run();
      stepperJ3.run();
    }
    delay(100);
  }
}
