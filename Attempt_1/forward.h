
double L1 = 228;    // L1 = 228mm
double L2 = 136.5;  // L2 = 136.5mm
double theta1, theta2, phi, z;

const float theta1AngleToSteps = 44.444444;
const float theta2AngleToSteps = 35.555555;
const float phiAngleToSteps = 10;
const float zDistanceToSteps = 100;

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