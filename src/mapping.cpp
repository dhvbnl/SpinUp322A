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
  drivetrainTurn(90);
  wait(200, msec);
  printf("inertial after %f \n", getInertialHeading());
  //setDrivetrainSpeed(3, 3);
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
       // wait(2, msec);
      }
      intake.spin(fwd, 60, pct);
      while (flywheelCheck.value(pct) < 50) { // wait for disk to pass flywheel
      //  printf("check %lo \n", flywheelCheck.value(pct));
        wait(10, msec);
      }
       i++;
       printf("disk count %i \n", i);
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
  int flywheelvel = flywheel.velocity(pct);
  printf("flywheel velocity before %f \n", flywheel.velocity(pct));
  indexnew(disks, flywheelvel);
  //flywheelmanual(0);

    
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

void leftroller(int roller) {
  setDrivetrainLock();
   int flywheelspeed = 12;
  flywheelmanual(flywheelspeed);
  timeDrive(-4, 500); //rolls rollers
  setIntakeSpeed(12);
  wait(roller, msec); // 200 match, 400 skills 
  setIntakeSpeed(0);
  timeDrive(4, 400);
  arcturn(5, 0, 60); //5 0 60
  arcturn2(-2.5, 5, 352); //-2.5 5 352
  printf("inertial %f \n", getInertialHeading());
  wait(1200, msec);
  testflywheel(flywheelspeed, 2);
  wait(100, msec);
//   timeDrive(-5, 600);
  drivetrainTurn(54);
  printf("inertial %f \n", getInertialHeading());
   //turn to three disk stack
 // setIntakeSpeed(12);
// timeDrive(3, 400);
  //wait(100, msec);
  flywheelmanual(11.6);
  setIntakeSpeed(12);
  timeDrive(3, 2000);
  wait(300, msec);
  arcturn(0, 5, 327);
  wait(500, msec);
  printf("inertial %f \n", getInertialHeading());
  testflywheel(flywheelspeed, 3);
  // timeDrive(-4, 500);
  // drivetrainTurn(333);
  // printf("inertial %f \n", getInertialHeading());
  // timeDrive(3, 500);
  // testflywheel(flywheelspeed, 2);
  // printf("reached %f \n", 0.0);
  // drivetrainTurn(44);
  // timeDrive(-4, 2500);


}

void bothrollers (color col, signature sig, int roller) {

  leftroller( roller);
  wait(200, msec);
  drivetrainTurn(226);
  timeDrive(-6, 2900);
  wait(100, msec);
  drivetrainTurn(270);
  timeDrive(-4, 1000);
  timeDrive(2, 300);
  setIntakeSpeed(12);
  wait(roller, msec);
  setIntakeSpeed(0);
 // timeDrive(3, 300);

}

void rightroller () {
  int flywheelspeed = 12;
  flywheelmanual(12);
  timeDrive(-6, 600);
  drivetrainTurn(90);
  timeDrive(-6, 500);
  setIntakeSpeed(12);
  wait(200, msec);
  setIntakeSpeed(0);
  timeDrive(3, 900);
  drivetrainTurn(98);
  wait(3000, msec);
  testflywheel(flywheelspeed, 2);
  setIntakeSpeed(12);
  drivetrainTurn(43);
  timeDrive(5, 2500);
  drivetrainTurn(135);
  timeDrive(5, 500);
  testflywheel(flywheelspeed, 3);
  // printf("reached %f \n", 0.0);
  
}

void skills (color col, signature sig) {
  bothrollers(col, sig, 400);
  timeDrive(3, 800);
  drivetrainTurn(180);
  timeDrive(-4, 1500);
  timeDrive(2, 300);
  setIntakeSpeed(12);
  wait(400, msec);
  setIntakeSpeed(0);
  timeDrive(4, 700);
  drivetrainTurn(226);
  expansion.set(false);
  wait(3, sec);
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