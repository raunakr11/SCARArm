// #FORWARD KINEMATICS
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#include "homing.h"
#include "forward.h"
#include "inverse.h"

#define LIMIT_SWITCH_PIN1 10
#define LIMIT_SWITCH_PIN2 9
#define LIMIT_SWITCH_PIN3 11
#define LIMIT_SWITCH_PIN4 A3

// Define the stepper motors and the pins the will use
// AccelStepper stepperJ1(1, 3, 6);  // (Type:driver, STEP, DIR)
// AccelStepper stepperJ2(1, 4, 7);
// AccelStepper stepperJ3(1, 2, 5);
// AccelStepper stepperJ4(1, 12, 13);

Servo gripperServo;

// double x = 10.0;
// double y = 10.0;
// double L1 = 228;    // L1 = 228mm
// double L2 = 136.5;  // L2 = 136.5mm
// double theta1, theta2, phi, z;

int stepperJ1Position, stepperJ2Position, stepperJ3Position, stepper4Position;

double x = 10.0;
double y = 10.0;

// const float theta1AngleToSteps = 44.444444;
// const float theta2AngleToSteps = 35.555555;
// const float phiAngleToSteps = 10;
// const float zDistanceToSteps = 100;

void homing() {
  homeJ4();
  homeJ2();
  homeJ3();
  homeJ1();
}


void setup() {
  Serial.begin(9600);
  gripperServo.attach(A0, 600, 2500);
  gripperServo.write(0);           // tell servo to go to position in variable 'pos'                                                                   
  // homing();
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


    // forwardKinematics();
    inverseKinematics(x, y);

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

    // Serial.print("stepperJ1 steps taken :");
    // Serial.println(stepperJ1Position);
    // Serial.print("stepperJ2 steps taken :");
    // Serial.println(stepperJ2Position);
    // Serial.print("stepperJ3 steps taken :");
    // Serial.println(stepperJ3Position);
    // Serial.print("Gripper position :");
    // Serial.println(serAngle);

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