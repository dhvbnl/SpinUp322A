#include "vex.h"

void testvision (color col, signature sig) {
   findGoal(red, REDGOAL, true);
  //setDrivetrainSpeed(-3.5, 3.5);
}
void testinertial () {
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
  printf("inertial before %f \n", getInertialHeading());
  drivetrainTurn(200);
  wait(200, msec);
  printf("inertial after %f \n", getInertialHeading());
  setDrivetrainSpeed(3, 3);
  wait(500, msec);
  setDrivetrainSpeed(0, 0);


}
void testflywheel (color col, signature sig) {
  printf("enterprogram %f \n", 1.0);
  // setIntakeSpeed(12);
  // wait(6000, msec);
  // setIntakeSpeed(0);
  int width = findGoal(col, sig, false);
  double flywheelvolt = -0.0004 * pow(width, 3) + 0.0672 * pow(width, 2) - 3.82 * width + 83.467;
  printf("flywheelvolt %f", flywheelvolt);
  if (flywheelvolt > 11.5) {
    flywheelvolt = 11.5;
  } 
  // if (width > 70) {
  //   flywheelvolt = 8.7;
  // } else if (width > 55) {
  //   flywheelvolt = 9;
  // } else if (width > 45) {
  //   flywheelvolt = 9.2;
  // } else {
  //   flywheelvolt = 11.5;
  // }
  //printf("volt %f \n", flywheelvolt);

    flywheelmanual(9.15);
    wait(5, sec);
    indexmanual(8, true);

    for (int i = 0; i < 2; i++) {
      wait(100, msec);
      indexmanual(0, false); // up
      wait(3000, msec);
      indexmanual(8, true);
    }
    
    
  //flywheelmanual(12);
}

void testarea(color col, signature sig) {
  v.setBrightness(150);
  v.takeSnapshot(sig);
   while (v.objectCount == 0 ||
          v.largestObject.height < 30 ||
          v.largestObject.width < 60) {
    wait(20, msec);
    v.takeSnapshot(sig);
  }
  printf("object found %f \n", 0.0);
  vision::object test = v.largestObject;
  while (true) {
    printf("area %f \n", double(test.width*test.height));
    printf("width %f \n", double(test.width));
    wait(3000, msec);
    printf("change %f \n", 0.0);
    v.takeSnapshot(sig);
  }
}