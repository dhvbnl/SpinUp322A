#include "vex.h"

void testvision (color col, signature sig, bool right) {
  // while (true) {
  //   int num = v.takeSnapshot(sig);
  //   printf("object found %f \n", 1.0 * num);
  //   wait(10, msec);
  // }
   findGoal(col, sig, right);
   //testflywheel();
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
      printf("flywheel velocity %f \n", flywheel.velocity(pct));
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

void testflywheel (int flywheelspeed, int disks) {

  //printf("enterprogram %f \n", 1.0);
  //double flywheelspeed = 90;
  flywheelmanual(flywheelspeed);
  while(flywheel.velocity(pct) < flywheelspeed) {
    printf("flywheel speed %f \n", flywheel.velocity(pct));
    wait(20, msec);
  }  
  //printf("flywheel velocity before %f \n", flywheel.velocity(pct));
  indexnew(disks, flywheelspeed);
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

void leftroller(color col, signature sig, int roller) {
  int flywheelspeed = 90;
  timeDrive(-4, 500); //rolls rollers
  setIntakeSpeed(12);
  wait(roller, msec); // 100 match, 200 skills 
  setIntakeSpeed(0);
  timeDrive(4, 400);
  drivetrainTurn(48); //turn to three disk stack
 
  printf("inertial %f \n", getInertialHeading());
  timeDrive(5, 2500);
  wait(200, msec);
  flywheelmanual(flywheelspeed);
  timeDrive(-4, 500);
  findGoal(col, sig, true);
  timeDrive(3, 500);
  testflywheel(flywheelspeed, 2);
  printf("reached %f \n", 0.0);


}

void bothrollers (color col, signature sig, int roller) {

  leftroller(col, sig, roller);
  wait(200, msec);
  drivetrainTurn(226);
  timeDrive(-6, 2600);
  wait(100, msec);
  drivetrainTurn(270);
  timeDrive(-4, 500);
  timeDrive(2, 200);
  setIntakeSpeed(12);
  wait(roller, msec);
  setIntakeSpeed(0);
  timeDrive(3, 300);

}

void rightroller (color col, signature sig) {
  int flywheelspeed = 95;
  timeDrive(-6, 600);
  drivetrainTurn(90);
  timeDrive(-6, 300);
  setIntakeSpeed(12);
  wait(100, msec);
  setIntakeSpeed(0);
  timeDrive(3, 300);
  drivetrainTurn(220);
  timeDrive(-5, 2500);
  wait(200, msec);
  flywheelmanual(flywheelspeed);
  timeDrive(3, 300);
  drivetrainTurn(160);
  findGoal(col, sig, false);
  testflywheel(flywheelspeed, 2);
  // printf("reached %f \n", 0.0);
  
}

void skills (color col, signature sig) {
  bothrollers(col, sig, 400);
  timeDrive(3, 500);
  drivetrainTurn(180);
  timeDrive(-4, 1800);
  timeDrive(2, 200);
  setIntakeSpeed(12);
  wait(400, msec);
  setIntakeSpeed(0);
  timeDrive(4, 700);
  drivetrainTurn(226);
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