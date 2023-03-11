#include "vex.h"

struct Acceleration {
  double dist;
  bool fwd;
  double deg;
  double maxspeed;
  double speedl; 
  double speedr; 
} acc;

double speed = 0;

double getLeftEncoder() {return leftFrontDrive.rotation(deg); }
double getRightEncoder() {return rightFrontDrive.rotation(deg);}
int movel(double speed, bool fwd) {
  if (fwd) {
     leftFrontDrive.spin(vex::directionType::fwd, speed, volt);
     leftMiddleDrive.spin(vex::directionType::fwd, speed, volt); 
     leftBackDrive.spin(vex::directionType::fwd, speed, volt);
    
  } else {
    leftFrontDrive.spin(vex::directionType::rev, speed, volt);
    leftMiddleDrive.spin(vex::directionType::rev, speed, volt); 
    leftBackDrive.spin(vex::directionType::rev, speed, volt);
  }
  return 0;
}
int mover(double speed, bool fwd) {
  if (fwd) {
    rightFrontDrive.spin(vex::directionType::fwd, speed, volt);
    rightMiddleDrive.spin(vex::directionType::fwd, speed, volt); 
    rightBackDrive.spin(vex::directionType::fwd, speed, volt);
    
  } else {
    rightFrontDrive.spin(vex::directionType::rev, speed, volt);
    rightMiddleDrive.spin(vex::directionType::rev, speed, volt); 
    rightBackDrive.spin(vex::directionType::rev, speed, volt);
  }
  return 0;

}
//accelerate
/*int accelerate() {
  //robot current position
  double lorig = getVerticalEncoderRotation() * convertInches;
  //if the robot is going forwards
  if (acc.fwd) {
    //distance we want the robot to go to + where robot currently is
    acc.dist += lorig;
    while ((getVerticalEncoderRotation() * convertInches) < acc.dist) {
      //speed = 4.0 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      speed = pow((fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig) + 0.5), 2) + 2.6;
      //if (speed > 11)
        //speed = 11;
      if (speed > acc.maxspeed)
        speed = acc.maxspeed;
      wait(10, msec);
    }
  //if the robot is going backwards
  } else {
    //distance we want the robot to go to - where the robot currently is (becaues the robot is going backwards)
    acc.dist = lorig - acc.dist;
    int x = 0;
    while ((getVerticalEncoderRotation() * convertInches) > acc.dist) {
      //speed = 3.2 * (fabs((fabs(getLeftEncoderRotation()) * convertInches) - lorig) + 1) + 2.6;
      
          x = lorig - (getVerticalEncoderRotation() * convertInches);
      
      speed = pow((x + 0.5), 2) + 2.6;
      //if (speed > 9)
       // speed = 9;
      if (speed > acc.maxspeed) 
        speed = acc.maxspeed;
      wait(10, msec);
    }
  }
  return 0;
}*/
void accelerate () {
  double M = acc.maxspeed; 
  double t = 2.8;
  double k = 0.7;


  //      1/(1+te^(-kx) 
  //logistic growth curve ("s" curve) 
  while ( fabs(getLeftEncoder() * convertInches) < 8 ||  fabs(getRightEncoder() * convertInches) < 8) {
    acc.speedl = M / (1 + t * exp(-k *  fabs(getLeftEncoder() * convertInches))); // x = position 
    acc.speedr = M / (1 + t * exp(-k *  fabs(getRightEncoder() * convertInches))); 
    wait(10, msec);
    // printf("leftencoder %f", getLeftEncoder() * convertInches);
    // printf("    rightencoder %f", getRightEncoder() * convertInches);
     //printf("   speed %f \n", acc.speedl);

  }
  
}
//decelerate
/*int decelerate() {
  //robot current position (in inches)
  double lorig = getVerticalEncoderRotation() * convertInches;
  int n = 0;
  //if the robot is going forward
  if (acc.fwd) {
    //changing "x" to make sure that the robot can decelerate properly no matter
    //the distance
    if (acc.dist < 14) {
      n = 14 - acc.dist;
    }
    //robot current position added to distance it needs to decelerate
    acc.dist += lorig;
    while ((getVerticalEncoderRotation() * convertInches) < acc.dist) {
      speed = -3.8 * log(fabs((fabs(getVerticalEncoderRotation()) * convertInches) - lorig + n)) + 11.7;
        if (speed > acc.maxspeed) speed = acc.maxspeed;
        wait(10, msec);
    }
  //if the robot is going backwards
  } else {
    //changing "x" to make sure that the robot can decelerate properly no matter
    //the distance
    if (acc.dist < 14) {
      n = 14 - acc.dist;
    }
    //distance it needs to decelerate subtracted from robot current position (because encoder reads going backwards as negative)
    acc.dist = lorig - acc.dist;
    int changeindist = 0;
    while ((getVerticalEncoderRotation() * convertInches) > acc.dist) {
      if (acc.dist < 14) {
        changeindist = lorig - (getVerticalEncoderRotation() * convertInches) + n;
      } else {
        changeindist = lorig - (getVerticalEncoderRotation() * convertInches);
      }
        
        
        speed = -3.8 *log(changeindist) + 10.5;
        if (speed > acc.maxspeed) speed = acc.maxspeed;
        //if (speed < 2.5) speed = 1.5;
        wait(10, msec);
    }
  }
  return 0;
}*/

void decelerate (){
  double M = acc.maxspeed; 
  //M = 12;
  double k; 
  double x; 
  leftMiddleDrive.resetRotation();
  rightMiddleDrive.resetRotation();

  if (M < 5) {
    k = 5.5;
    x = 2;
  } else if (M < 9) {
    k = 5;
    x = 13; 
  } else {
    k = 6; 
    x = 18;
  }
  //  logistic growth curve ("s" curve)
  // M < 5; k = 2; x = 4
  // M < 9; k = 1; x = 8
  // M <= 12; k = 0.5; x = 13
  while (fabs(leftMiddleDrive.rotation(deg) * convertInches) < x ||  fabs(rightMiddleDrive.rotation(deg) * convertInches) < x) {
    //acc.speedl = (M / (1 + 0.01 * exp (k *  fabs(leftMiddleDrive.rotation(deg) * convertInches))));
   // acc.speedr = (M / (1 + 0.01 * exp (k *  fabs(rightMiddleDrive.rotation(deg) * convertInches))));
    acc.speedl = M * exp(-fabs(leftMiddleDrive.rotation(deg)) *convertInches / k +.5);
    acc.speedr = M * exp(-fabs(rightMiddleDrive.rotation(deg)) * convertInches / k) + .5;
    // printf("leftencoder %f", getLeftEncoder() * convertInches);
    // //printf("    rightencoder %f", getRightEncoder() * convertInches);
    // printf("   speeddec %f \n", acc.speedl);
    wait(10, msec);
  }

 
}

void driveProfile(int dist, double maxspeed, bool fwd) { 
  setDrivetrainLock();
  acc.dist = dist; 
  acc.maxspeed = maxspeed; 
  leftFrontDrive.resetRotation();
  rightFrontDrive.resetRotation();
  double startvalL = getLeftEncoder() * convertInches; 
  double startvalR = getRightEncoder() * convertInches; 
  int enddist; 
  
  if (maxspeed < 5) {
    enddist = 2;
  } else if (maxspeed < 9) {
    //printf("speed done %f \n", 0.0);
    enddist = 13;
  } else {
    enddist = 18; 
  }

  if (dist < maxspeed + enddist) {
    thread acc1(accelerate);
    while (fabs(getLeftEncoder() * convertInches) - startvalL < dist/2 && fabs(getRightEncoder() * convertInches) - startvalR < dist/2) {
      movel(acc.speedl, fwd);
      mover(acc.speedr, fwd);
      wait(10, msec);
    }
   // printf("accel done %f \n", 0.0);
    acc1.interrupt();
    thread dec1(decelerate);
    while (fabs(getLeftEncoder() * convertInches) - startvalL < dist && fabs(getRightEncoder() * convertInches) - startvalR < dist) {
      movel(acc.speedl, fwd);
      mover(acc.speedr, fwd);
      wait(10, msec);
    }
    dec1.interrupt();
  } else { 
    thread acc2(accelerate);
    while (fabs(getLeftEncoder() * convertInches) - startvalL < 8 && fabs(getRightEncoder() * convertInches) - startvalR < 8) {
      movel(acc.speedl, fwd);
      mover(acc.speedr, fwd);
      wait(10, msec);
      // printf("leftencoder %f", getLeftEncoder() * convertInches);
      // printf("    rightencoder %f \n", getRightEncoder() * convertInches);
    }
    acc2.interrupt();
    //printf("accel done %f \n", 0.0);
    while (fabs(getLeftEncoder() * convertInches) - startvalL < (dist - enddist) && fabs(getRightEncoder() * convertInches) - startvalR < (dist - enddist)) {
     // printf("maxspeed %f \n", getLeftEncoder() * convertInches);
      movel(maxspeed, fwd);
      mover(maxspeed, fwd);
      wait(10, msec);
    }
    //printf("done with maxspeed %f \n", getLeftEncoder() * convertInches);
    thread dec2(decelerate);
    while (fabs(getLeftEncoder() * convertInches) - startvalL < dist && fabs(getRightEncoder() * convertInches) - startvalR < dist) {
     // printf("decel %f \n", getLeftEncoder() * convertInches);
      movel(acc.speedl, fwd);
      mover(acc.speedr, fwd);
      wait(10, msec);
      // printf("dec %f", getLeftEncoder() * convertInches);
      // printf("    dec %f \n", getRightEncoder() * convertInches);
  
    }
    dec2.interrupt();
   // printf("decdone %f \n", acc.speedl);
  }
 


  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
   

  //add special case for when the total distance is less than what it is supposed to be 
  printf("leftencoder %f", getLeftEncoder() * convertInches);
  printf("    rightencoder %f \n", getRightEncoder() * convertInches);
  


  
  
}

void testmotionprofile(int dist) {
  driveProfile(10, 5, true);
  wait(100, msec);

 
}

/*int driveProfile(int dist, double maxspeed, bool fwd) { //encoder orientation flipped
  //Inertial.resetRotation();
  acc.dist = 0;
  double acceldist = 0;
  int targetL = 0;
  double actdist;
  acc.maxspeed = maxspeed;
 
  //determines acceleration and deceleration distance
  if (dist > 28) 
  {
    acceldist = 14;
  } 
  else {
    acceldist = dist / 2.0;
  }
  // Switching units to degrees here
  dist *= convertDegrees;
 
  if (fwd) {
    actdist = getVerticalEncoderRotation() + dist;
  } 
  else {
    actdist = getVerticalEncoderRotation() - dist;
  }
  //going forward
  if (fwd)  {
    acc.dist = acceldist; // feeding acc.dist inch value -- accelerate() handles inches
    acc.fwd = fwd;

    thread thread1(accelerate);

    // accelerate-- switch to degrees
    acceldist *= convertDegrees;
    targetL = getVerticalEncoderRotation() + acceldist; // target to finish acceleration
   
    while (getVerticalEncoderRotation() < targetL) {
      move(speed, true);
      wait(10, msec);
    }
    thread1.interrupt();
    while (getVerticalEncoderRotation() < (actdist - acceldist)) {
      move(maxspeed, true);
     // printf(" encodermax: %f\n", getVerticalEncoderRotation() * convertInches);
    } 
    acc.dist = acceldist * convertInches;
    thread thread3(decelerate);
    // decelerate
    //targetL = getVerticalEncoderRotation() + acceldist;
    
    while (getVerticalEncoderRotation() < actdist ) {
      move(speed, true);
    //  printf(" encoderdes: %f\n", getVerticalEncoderRotation() * convertInches);
    }
    thread3.interrupt();
  } 
  //backwards
  else {
    acc.dist = acceldist;
    acc.fwd = fwd;
    acceldist *= convertDegrees;
   
    thread thread2(accelerate);
    // accelerate
    targetL = getVerticalEncoderRotation() - acceldist;
   
    while ((getVerticalEncoderRotation() > targetL)) {
     // printf("accelerate: %f\n", speed);
      move(speed, false);
     // printf(" encoderacc: %f\n", getVerticalEncoderRotation() * convertInches);
      wait(10, msec);
    }
    thread2.interrupt();
   
    while (getVerticalEncoderRotation() > (actdist + acceldist)) {
      move(maxspeed, false);
    //  printf(" encodermax: %f\n", getVerticalEncoderRotation() * convertInches);
    }


    acc.dist = acceldist * convertInches;
    //decelerate
    thread thread4(decelerate);
    targetL = getVerticalEncoderRotation() - acceldist;
    while (getVerticalEncoderRotation() > targetL) {
      //printf("decelerate %f\n", speed);
     // printf(" encoderdes: %f\n", getVerticalEncoderRotation() * convertInches);
      move(speed, false);
    } 
    thread4.interrupt();   
  }
 
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
  wait(100, msec);
  //printf("done with motion profile");
  return 0;
}*/


