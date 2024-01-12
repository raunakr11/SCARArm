// double x = 10.0;
// double y = 10.0;
// double L1 = 228; // L1 = 228mm
// double L2 = 136.5; // L2 = 136.5mm
// double theta1, theta2, phi, z;


// const float theta1AngleToSteps = 44.444444;
// const float theta2AngleToSteps = 35.555555;
// const float phiAngleToSteps = 10;
// const float zDistanceToSteps = 100;


// INVERSE KINEMATICS
void inverseKinematics(double x, double y) {
  theta2 = acos((sq(x) + sq(y) - sq(L1) - sq(L2)) / (2 * L1 * L2));
  if (x < 0 && y < 0) {
    theta2 = (1) * theta2;
  }
  
  // theta1 = atan(x / y) - atan((L2 * sin(theta2)) / (L1 + L2 * cos(theta2)));
  theta1 = atan(y / x) - atan((L2 * sin(theta2)) / (L1 + L2 * cos(theta2)));
  theta2 = (-1) * theta2 * 180 / PI;
  theta1 = theta1 * 180 / PI;

 // Angles adjustment depending in which quadrant the final tool coordinate x,y is
  if (x >= 0 && y >= 0) {       // 1st quadrant
    theta1 = 90 - theta1;
  }
  else if (x < 0 && y > 0) {       // 2nd quadrant
    theta1 = 90 - theta1;
  }
  else if (x < 0 && y < 0) {       // 3d quadrant
    theta1 = 270 - theta1;
    phi = 270 - theta1 - theta2;
    phi = (-1) * phi;
  }
  else if (x > 0 && y < 0) {       // 4th quadrant
    theta1 = -90 - theta1;
  }
  else if (x < 0 && y == 0) {
    theta1 = 270 + theta1;
  }
  
  // Calculate "phi" angle so gripper is parallel to the X axis
  phi = 90 + theta1 + theta2;
  phi = (-1) * phi;

  // Angle adjustment depending in which quadrant the final tool coordinate x,y is
  if (x < 0 && y < 0) {       // 3d quadrant
    phi = 270 - theta1 - theta2;
  }
  if (abs(phi) > 165) {
    phi = 180 + phi;
  }

  theta1=round(theta1);
  theta2=round(theta2);
  phi=round(phi);//The third angle which I call “phi” is be used for setting the orientation of the gripper.

}
