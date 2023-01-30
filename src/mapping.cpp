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

int indexerauton(int count) {
  while(flywheelCheck.value(pct) >= 40) { // disc not in place it should be
    indexer.spin(fwd, 12, volt);
    wait(30, msec);
  }
  indexer.spin(fwd, -5, volt);
  wait(30, msec);
  indexer.spin(fwd, 0, volt);
  count++;
  return count;
}

void leftroller(color col, signature sig) {
  timeDrive(4, 500);
  setIntakeSpeed(-7);
  wait(150, msec);
  setIntakeSpeed(0);
  timeDrive(-4, 400);
  drivetrainTurn(353);
  flywheelmanual(10.7);
  setindexerClamp();
  wait(3, sec);
  int count = 0;
  while (count < 2 ) {
    count = indexerauton(count);
    printf("count %f \n", double(count));
    wait(1200, msec); //2000
  }
  setindexerClamp();
  drivetrainTurn(235);
  setIntakeSpeed(12);
  printf("inertial %f \n", getInertialHeading());
  timeDrive(5, 2000);
  wait(200, msec);
  flywheelmanual(10);
  drivetrainTurn(310);
  wait(500, msec);
  setIntakeSpeed(0);
  findGoal(col, sig, true);
  printf("reached %f \n", 0.0);
  count = 0;
 // timer t;
  wait(1000, msec);
  setindexerClamp();
  while (count < 3 ) {
    count = indexerauton(count);
    printf("count %f \n", double(count));
    wait(1200, msec); //2000
  }
}

void bothrollers (color col, signature sig) {
  leftroller(col, sig);
  printf("done %f \n", 0.0);
  flywheelmanual(0);
  setindexerClamp();
  drivetrainTurn(207);
  setIntakeSpeed(12);
  timeDrive(9, 2500);
  setIntakeSpeed(0);
  drivetrainTurn(270);
  timeDrive(6, 300);
  setIntakeSpeed(-7);
  wait(150, msec);
  setIntakeSpeed(0);
  timeDrive(4, -700);

}

void rightroller (color col, signature sig) {
  timeDrive(6, 700);
  drivetrainTurn(90);
  timeDrive(6, 300);
  setIntakeSpeed(-7);
  wait(100, msec);
  setIntakeSpeed(0);
  timeDrive(4, -700);
  drivetrainTurn(220);
  setIntakeSpeed(12);
  timeDrive(5, 1500);
  wait(200, msec);
  flywheelmanual(10);
  drivetrainTurn(170);
  wait(500, msec);
  setIntakeSpeed(0);
  findGoal(col, sig, false);
  printf("reached %f \n", 0.0);
  int count = 0;
 // timer t;
  wait(1000, msec);
  setindexerClamp();
  while (count < 3 ) {
    count = indexerauton(count);
    printf("count %f \n", double(count));
    wait(1200, msec); //2000
  }
  
}

void skills (color col, signature sig) {
  leftroller(col, sig);
  wait(1000, sec);
  drivetrainTurn(getInertialHeading() + 90);
  wait(100, msec);
  timeDrive(5, 500);
  expansion.set(true);

}