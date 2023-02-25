#include "vex.h"

void testvision (color col, signature sig) {
  // while (true) {
  //   int num = v.takeSnapshot(sig);
  //   printf("object found %f \n", 1.0 * num);
  //   wait(10, msec);
  // }
   findGoal(col, sig, false);
   testflywheel();
  //setDrivetrainSpeed(-3.5, 3.5);
}
void testinertial () {
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
  printf("inertial before %f \n", getInertialHeading());
  drivetrainTurn(120);
  wait(200, msec);
  printf("inertial after %f \n", getInertialHeading());
  setDrivetrainSpeed(3, 3);
  wait(500, msec);
  setDrivetrainSpeed(0, 0);
  printf("inertial final %f \n", getInertialHeading());

}
void testrollers() {
  timeDrive(-5, 500);
  intake.spin(fwd, 12, volt);
  wait(300, msec);
  intake.stop();
  timeDrive(5, 200);
}

// int indexerauton(int count, double velbefore) {
//   // while(flywheelCheck.value(pct) >= 40) { // disc not in place it should be
//   while (flywheel.velocity(pct) >= velbefore) {
//     indexer.spin(fwd, 12, volt);
//     wait(30, msec);
//   }
//   indexer.spin(fwd, -5, volt);
//   wait(30, msec);
//   indexer.spin(fwd, 0, volt);
//   count++;
//   return count;
// }

void indexnew(int count, double velbefore) {
  int i = 0;
  while (i < count) {
    if (flywheel.velocity(pct) >= velbefore - 1 && flywheel.velocity(pct) <= velbefore + 1) {
     // printf("flywheel velocity %f \n", flywheel.velocity(pct));
      intake.spin(fwd, -100, pct); // spin indexer
      while(flywheelCheck.value(pct) > 50) { // wait for disk to reach flywheel
      //  printf("waitforflywheel %lo \n", flywheelCheck.value(pct));
        wait(10, msec);
      }
      intake.spin(fwd, 60, pct);
      while (flywheelCheck.value(pct) < 50) { // wait for disk to pass flywheel
      //  printf("check %lo \n", flywheelCheck.value(pct));
        wait(10, msec);
      }
       i++;
    }
    //printf("disk count %i \n", i);
   // intake.spin(fwd, 60, pct);
    intake.stop();
    wait(20, msec);
  } 

}

void testflywheel () {

  //printf("enterprogram %f \n", 1.0);
  double flywheelspin = 95;
  flywheelmanual(flywheelspin);
  while(flywheel.velocity(pct) < flywheelspin) {
    wait(20, msec);
  }
  //printf("flywheel velocity before %f \n", flywheel.velocity(pct));
  indexnew(3, flywheelspin);
  flywheelmanual(0);

    
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

void leftroller(color col, signature sig) {
  timeDrive(4, 500);
  setIntakeSpeed(-7);
  wait(150, msec);
  setIntakeSpeed(0);
  timeDrive(-4, 400);
  drivetrainTurn(353);
  flywheelmanual(10.7);
  //setindexerClamp();
  wait(3, sec);
  int count = 0;
  while (count < 2 ) {
    //count = indexerauton(count, 0);
    printf("count %f \n", double(count));
    wait(1200, msec); //2000
  }
  //setindexerClamp();
  drivetrainTurn(235);
  setIntakeSpeed(12);
  printf("inertial %f \n", getInertialHeading());
  timeDrive(5, 2000);
  wait(200, msec);
  flywheelmanual(10);
  drivetrainTurn(310);
  wait(500, msec);
  setIntakeSpeed(0);
  printf("reached %f \n", 0.0);
  count = 0;
 // timer t;
  wait(1000, msec);
  //setindexerClamp();
  while (count < 3 ) {
    //count = indexerauton(count, 0);
    printf("count %f \n", double(count));
    wait(1200, msec); //2000
  }
}

void bothrollers (color col, signature sig) {
  timeDrive(4, 500);
  //setIntakeSpeed(-7);
  wait(150, msec);
  //setIntakeSpeed(0);
  timeDrive(-4, 400);
  // printf("done %f \n", 0.0);
  
  drivetrainTurn(230);
  printf("inertial %f \n", getInertialHeading());
  //setIntakeSpeed(12);
  timeDrive(9, 2500);
  //setIntakeSpeed(0);
  drivetrainTurn(270);
  timeDrive(6, 300);
  //setIntakeSpeed(-7);
  wait(150, msec);
  //setIntakeSpeed(0);
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
  //setindexerClamp();
  while (count < 3 ) {
    //count = indexerauton(count, 0);
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

void straightline(double speed, int timedrive) {
  timer t; 
  while (t.time(msec) < timedrive) {
    leftFrontDrive.spin(fwd, speed, pct);
    rightFrontDrive.spin(fwd, speed, pct);
    leftBackDrive.spin(fwd, speed, pct);
    rightBackDrive.spin(fwd, speed, pct);

    if (leftFrontDrive.velocity(pct) < speed) {
      leftFrontDrive.spin(fwd, speed + 2, pct);
      rightFrontDrive.spin(fwd, speed - 2, pct);
      leftBackDrive.spin(fwd, speed + 2, pct);
      rightBackDrive.spin(fwd, speed - 2, pct);
    }
    if (rightFrontDrive.velocity(pct) < speed) {
      leftFrontDrive.spin(fwd, speed - 2, pct);
      rightFrontDrive.spin(fwd, speed + 2, pct);
      leftBackDrive.spin(fwd, speed - 2, pct);
      rightBackDrive.spin(fwd, speed + 2, pct);
    }
    printf("time %f \n", t.time(msec));
    wait(20, msec);
  }
  leftFrontDrive.spin(fwd, 0, pct);
  rightFrontDrive.spin(fwd, 0, pct);
  leftBackDrive.spin(fwd, 0, pct);
  rightBackDrive.spin(fwd, 0, pct);
}