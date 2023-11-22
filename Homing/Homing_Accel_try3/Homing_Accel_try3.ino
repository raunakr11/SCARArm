// #include <AccelStepper.h>

// #define STEP_PIN 2
// #define DIR_PIN 5
// #define LIMIT_SWITCH_PIN 11

// AccelStepper stepper(1, STEP_PIN, DIR_PIN);

// void setup() {
//   Serial.begin(9600);
//   pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

//   stepper.setMaxSpeed(3000);
//   stepper.setAcceleration(1000);
//   stepper.setSpeed(1000);

//   int flag = 0;

//   while(digitalRead(LIMIT_SWITCH_PIN) == LOW)
//   {
//     stepper.runSpeed(); // Run the stepper motor at the set speed
//     if(digitalRead(LIMIT_SWITCH_PIN) == HIGH) break;
//   }

  
//   // stepper.runSpeed(); // Run the stepper motor at the set speed

//   // stepper.setSpeed(-1000);
//   // stepper.move(100);

//   // stepper.runSpeed(); // Run the stepper motor at the set speed
//   // // stepper.runSpeedToPosition(false);

// stepper.stop(); // Stop the motor

//   // Change direction and move in the opposite direction
//   stepper.setSpeed(-6000); // Set the speed in the opposite direction
//   stepper.setAcceleration(1000);
//   stepper.move(-2000); // Move 100 steps in the opposite direction

//   // Run the motor until it reaches the desired position
//   while (stepper.distanceToGo() != 0) {
//     stepper.runSpeed();
//   }
  
  
// }

// void loop() {
// }


#include <AccelStepper.h>

#define STEP_PIN 2
#define DIR_PIN 5
#define LIMIT_SWITCH_PIN 11

AccelStepper stepper(1, STEP_PIN, DIR_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(1000);
  stepper.setSpeed(3000);

  int flag = 0;

  while(digitalRead(LIMIT_SWITCH_PIN) == LOW) {
    stepper.runSpeed(); // Run the stepper motor at the set speed
    if(digitalRead(LIMIT_SWITCH_PIN) == HIGH) break;
  }

  // stepper.stop(); // Stop the motor

  // Set speed and acceleration for the downward movement
  stepper.setSpeed(-3000);
  stepper.setAcceleration(1000);
  stepper.move(-5000);

  while (stepper.distanceToGo() != 0) {
    Serial.println(stepper.distanceToGo());
    stepper.runToPosition();
  }
}
void loop() {

}
