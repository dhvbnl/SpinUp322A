#include "vex.h"

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
struct flywheel {
  double speed; 
} fly;

void flywheelauton(){
  while (true) {
  int currentVelocity = flywheel.velocity(pct);
  int speed = fly.speed / voltageConverstion;
 // printf("flywheel speed %i \n", speed);

  if(currentVelocity < fly.speed - 1){
    speed += (fly.speed - currentVelocity)/2;
  } else if(currentVelocity > fly.speed + 1){
    speed += (fly.speed - currentVelocity)/2;
  }
    flywheel.spin(fwd, speed, volt);
  wait(10,msec);
  }
}

void testploop() {
  printf("test %f \n", 0.0);
  setIntakeSpeed(12);
  //timeDrive(2.5, 2000);
}

void indexnew(int count, double velbefore) {
  int i = 0;
  timer t;
  while (i < count && t.time(msec) < 4000) {
    if (flywheel.velocity(pct) >= velbefore - 1 && flywheel.velocity(pct) <= velbefore + 1 && t.time(msec) < 5000) {
     // printf("flywheel velocity %f \n", flywheel.velocity(pct));
      intake.spin(fwd, -100, pct); // spin indexer
      while(flywheelCheck.value(pct) > 50 && t.time(msec) < 5000) { // wait for disk to reach flywheel
      //  printf("waitforflywheel %lo \n", flywheelCheck.value(pct));
       wait(10, msec);
      }
      intake.spin(fwd, 60, pct);
      while (flywheelCheck.value(pct) < 50 && t.time(msec) < 5000) { // wait for disk to pass flywheel
      //  printf("check %lo \n", flywheelCheck.value(pct));
        wait(10, msec);
      }
       i++;
       printf("disk count %i \n", i);
    }
    //printf("disk count %i \n", i);
   // intake.spin(fwd, 60, pct);
    intake.stop();
    //printf("time %f \n", t.time(msec));
    wait(20, msec);


  } 

}

void testflywheel (int flywheelspeed, int disks) {

  //printf("enterprogram %f \n", 1.0);
  //double flywheelspeed = 90;
  int flywheelvel = flywheel.velocity(pct);
  indexnew(disks, flywheelvel);
  //flywheelmanual(0);

    
  //flywheelmanual(12);
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
  arcturn2(-3, 5, 354); //-2.5 5 352
  printf("inertial %f \n", getInertialHeading());
  wait(1200, msec);
  testflywheel(flywheelspeed, 2);
  wait(100, msec);
  drivetrainTurn(54);
  printf("inertial %f \n", getInertialHeading());
   //turn to three disk stack

  flywheelmanual(11.6);
  setIntakeSpeed(12);
  timeDrive(3, 800);
  // wait(300, msec);
  threestack(3, 1000);
  arcturn(0, 5, 333);
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
  drivetrainTurn(85);
  timeDrive(-6, 400);
  setIntakeSpeed(12);
  wait(300, msec);
  setIntakeSpeed(0);
  timeDrive(4, 400);
  wait(100, msec);
  drivetrainTurn(100);
  wait(2500, msec);
  testflywheel(flywheelspeed, 2);
  setIntakeSpeed(12);
  drivetrainTurn(48);
  driveProfile(80, 6, true);
   wait(500, msec); 
 // timeDrive(5, 2500);
  drivetrainTurn(122);
  //timeDrive(5, 500);
  wait(500, msec); 
  testflywheel(flywheelspeed, 2);
  // printf("reached %f \n", 0.0);
  
}
void threestack(double speed, int movetime) {
  setIntakeSpeed(12);
  while (intakeCheck.value(pct) > 10) {
    setDrivetrainSpeed(1.5, 1.5);
    wait(10, msec);
  }
  setDrivetrainSpeed(0, 0);
  while (intakeCheck.value(pct) < 10) {
    wait(10, msec);
    printf("wait %f \n", 0.0);
  }
  wait(1000, msec);
  while (intakeCheck.value(pct) > 10) {
    setDrivetrainSpeed(1.5, 1.5);
    wait(10, msec);
  }
  setDrivetrainSpeed(0, 0);
  while (intakeCheck.value(pct) < 10) {
    wait(10, msec);
    printf("wait %f \n", 1.0);
  }
  wait(1000, msec);
  printf("moveagain %f \n", 1.0);
  timeDrive(speed, movetime-700);
}
void skills () {
  setDrivetrainLock();
 
  flywheelmanual(12);
 // fly.speed = 89; //flywheel speed change 
  
  timeDrive(-4, 500); //rolls rollers
  setIntakeSpeed(12);
  wait(500, msec); // 200 match, 400 skills 
  setIntakeSpeed(0);
  timeDrive(4, 900);
  drivetrainTurn(357);
  wait(2500, msec);
  testflywheel(12, 2);
 
  thread flythread(flywheelauton);
   fly.speed = 80; 
  //get three stack 
  setIntakeSpeed(12);
  threestack(2, 2300);
  //timeDrive(3, 1800);
  wait(500, msec);
  
 //flywheel speed change 
  drivetrainTurn(71); // 72
  //roll rollers
  timeDrive(-5, 1500);
  wait(300, msec);
  timeDrive(4, 600);
  drivetrainTurn(10);
  driveProfile(35, 5, true);
  //shoot disks
  testflywheel(80, 3);

  fly.speed = 80;
  wait(500, msec);
  driveProfile(17, 5, false);
  setIntakeSpeed(12);
  //turn to three singles 
  drivetrainTurn(39);//40
  driveProfile(100, 5, true);
  drivetrainTurn(313);
  wait(500, msec);
  //shoot disks
  testflywheel(80, 3); 
  wait(500, msec); 
  drivetrainTurn(37);
  wait(100, msec);
  //get threestack 
  fly.speed = 83;
  setDrivetrainSpeed(4, 4);
  wait(400, msec);
  threestack(2, 2500);
  //timeDrive(2, 5000);
  wait(100, msec);
  drivetrainTurn(290);
  //shoots disks 
  testflywheel(83, 3);
  //rollers
  setIntakeSpeed(12);
  driveProfile(10, 4, true);
  arcturn(-7,-1.5, 200);
  timeDrive(-7, 700);
  wait(400, msec);
  //pick up disks 
  fly.speed = 82;
  timeDrive(4, 400);
  drivetrainTurn(165);
  threestack(2, 1500);
  wait(500, msec);
  //driveProfile(15, 4, false);
  drivetrainTurn(260);
  timeDrive(-6, 1200);
  wait(400, msec);
  setIntakeSpeed(0);
  timeDrive(5, 500);
  drivetrainTurn(192);
  driveProfile(30, 6, true);
  testflywheel(80, 3);
  timeDrive(-6, 1000);
  wait(100, msec);
  timeDrive(6, 300);
  drivetrainTurn(225);
  expansion.set(true);
  wait(1, sec);
  expansion.set(false);


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