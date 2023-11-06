#include <TimerOne.h>

const int limitSwitchPin = 11;  // The digital pin connected to the limit switch
int switchState = LOW;  // Initialize switchState to LOW
int lastSwitchState = LOW;  // Initialize lastSwitchState to LOW

void setup() {
  pinMode(limitSwitchPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  Serial.begin(9600);

  Timer1.initialize(1000);  // Set the timer to trigger every 1000 milliseconds (1 second)
  Timer1.attachInterrupt(checkLimitSwitch);
}

void loop() {
  // Your main code here
}

void checkLimitSwitch() {
  switchState = digitalRead(limitSwitchPin);

  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      // The limit switch is pressed
      Serial.println("Limit switch pressed");
    } else {
      // The limit switch is released
      Serial.println("Limit switch released");
    }
    lastSwitchState = switchState;
  }
}
