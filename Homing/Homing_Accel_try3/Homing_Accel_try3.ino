#include <AccelStepper.h>

#define LIMIT_SWITCH_PIN3 11
#define LIMIT_SWITCH_PIN1 10
#define LIMIT_SWITCH_PIN2 9
#define LIMIT_SWITCH_PIN4 A3

AccelStepper stepperJ3(1, 2, 5);
AccelStepper stepperJ1(1, 3, 6);
AccelStepper stepperJ2(1, 4, 7);
AccelStepper stepperJ4(1, 12, 13);

void homing()
{
  homeJ3();
  homeJ1();
  homeJ2();
  homeJ4();
}

void homeJ3()
{
  pinMode(LIMIT_SWITCH_PIN3, INPUT_PULLUP);

  stepperJ3.setMaxSpeed(5000);
  stepperJ3.setAcceleration(1000);
  stepperJ3.setSpeed(1500);

  while(digitalRead(LIMIT_SWITCH_PIN3) == LOW) {
    stepperJ3.runSpeed();
    if(digitalRead(LIMIT_SWITCH_PIN3) == HIGH) break;
  }

  // stepper.stop(); // Stop the motor

  stepperJ3.setSpeed(-3000);
  stepperJ3.move(-11000);

  while (stepperJ3.distanceToGo() != 0) {
    // Serial.println(stepper.distanceToGo());
    stepperJ3.runToPosition();
  }
  stepperJ3.
}


void homeJ1()
{
  pinMode(LIMIT_SWITCH_PIN1, INPUT_PULLUP);

  stepperJ1.setMaxSpeed(5000);
  stepperJ1.setAcceleration(1000);
  stepperJ1.setSpeed(1500);

  while(digitalRead(LIMIT_SWITCH_PIN1) == LOW) {
    stepperJ1.runSpeed();
    if(digitalRead(LIMIT_SWITCH_PIN1) == HIGH) break;
  }

  // stepper.stop(); // Stop the motor

  stepperJ1.setSpeed(-3000);
  stepperJ1.move(-8000);

  while (stepperJ1.distanceToGo() != 0) {
    // Serial.println(stepper.distanceToGo());
    stepperJ1.runToPosition();
  }
}
void homeJ2()
{
  pinMode(LIMIT_SWITCH_PIN2, INPUT_PULLUP);

  stepperJ2.setMaxSpeed(5000);
  stepperJ2.setAcceleration(1000);
  stepperJ2.setSpeed(1500);

  while(digitalRead(LIMIT_SWITCH_PIN2) == LOW) {
    stepperJ2.runSpeed();
    if(digitalRead(LIMIT_SWITCH_PIN2) == HIGH) break;
  }

  // stepper.stop(); // Stop the motor

  stepperJ2.setSpeed(-3000);
  stepperJ2.move(-5500);

  while (stepperJ2.distanceToGo() != 0) {
    // Serial.println(stepper.distanceToGo());
    stepperJ2.runToPosition();
  }
}
void homeJ4()
{
  pinMode(LIMIT_SWITCH_PIN4, INPUT_PULLUP);

  stepperJ4.setMaxSpeed(5000);
  stepperJ4.setAcceleration(1000);
  stepperJ4.setSpeed(1500);

  while(digitalRead(LIMIT_SWITCH_PIN4) == LOW) {
    stepperJ4.runSpeed();
    if(digitalRead(LIMIT_SWITCH_PIN4) == HIGH) break;
  }

  // stepper.stop(); // Stop the motor

  stepperJ4.setSpeed(-3000);
  stepperJ4.move(-1500);

  while (stepperJ4.distanceToGo() != 0) {
    // Serial.println(stepper.distanceToGo());
    stepperJ4.runToPosition();
  }
}


void setup() {
  Serial.begin(9600);

  homing();
  
}
void loop() {

}
