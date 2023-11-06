// defines pins
#define stepPin 4
#define dirPin 7 
#define limitSwitch1 11
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(limitSwitch1, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  int limitval = digitalRead(limitSwitch1);
  // Makes 200 pulses for making one full cycle rotation
  if(digitalRead(limitSwitch1) != 1){
    Serial.print("Going up  :  Switch is closed =   ");
    Serial.println(limitval);
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); } 
  }
  else if(digitalRead(limitSwitch1) ==1){
    Serial.print("Going Down  :  Switch is open =  ");
    Serial.println(limitval);
    digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < 2400; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(2500);
  }
  delay(1000);
  }
}