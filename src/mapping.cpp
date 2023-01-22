#include "vex.h"

void testvision (color col, signature sig) {
   findGoal(red, REDGOAL, false);
  //setDrivetrainSpeed(-3.5, 3.5);
}
void testinertial () {
  // printf("inertial before %f \n", getInertialHeading());
  // drivetrainTurn(90);
  // printf("inertial after %f \n", getInertialHeading());
    while(inert.isCalibrating()) {
    wait(100, msec);
  }
  while (true) {
    printf("inertial after %f \n", getInertialHeading());
    wait(200, msec);
  }

}
void testflywheel (color col, signature sig) {

  int width = findGoal(blue, BLUEGOAL, false);
  double flywheelvolt = -0.0004*pow(width, 3) + 0.0672 * pow (width, 2) - 3.82 * width + 83.467;
  if (flywheelvolt > 11.5) {
    flywheelvolt = 11.5;
  } 
  if (width > 70) {
    flywheelvolt = 9;
  } else if (width > 55) {
    flywheelvolt = 9.3;
  } else if (width > 45) {
    flywheelvolt = 9.6;
  } else {
    flywheelvolt = 11.5;
  }
  printf("volt %f \n", flywheelvolt);
    flywheelmanual(flywheelvolt);
    wait(3, sec);
    indexmanual(8, true);
    wait(100, msec);
    indexmanual(0, false);
    wait(2000, msec);
    indexmanual(8, true);

    
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