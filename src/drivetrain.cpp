#include "vex.h"

int stopTimer = 0;

//thread for drivetrain to respond to joystick movements
void drivetrainControl() {
  while (true) {
    //set speed based on inputs
    setDrivetrainSpeed(getLeftSpeedInLinear(), getRightSpeedInLinear());
    //setDrivetrainStopping();
    //stopTimer++;
    wait(10, msec);
  }
}
// setters

//sets speed of drivetrain based on left and right velocity inputs
void setDrivetrainSpeed(double leftSpeed, double rightSpeed) {
  leftFrontDrive.spin(fwd, leftSpeed, volt);
  leftBackDrive.spin(fwd, leftSpeed, volt);
  rightFrontDrive.spin(fwd, rightSpeed, volt);
  rightBackDrive.spin(fwd, rightSpeed, volt);
}

void setDrivetrainStopping(){
  if(stopTimer > 100 && (abs(getLeftBackVelocity()) > 0 || abs(getRightBackVelocity()) > 0)){
    setDrivetrainLock();
    if(getAxis3Pos() != 0)
      stopTimer = 0;
  } else{
    setDrivetrainCreep();
  }
}

void setDrivetrainCreep() {
  leftFrontDrive.setStopping(coast);
  leftBackDrive.setStopping(coast);
  rightFrontDrive.setStopping(coast);
  rightBackDrive.setStopping(coast);
}
void setDrivetrainLock() {
  leftFrontDrive.setStopping(brake);
  leftBackDrive.setStopping(brake);
  rightFrontDrive.setStopping(brake);
  rightBackDrive.setStopping(brake);
}

void setDrivetrainHold() {
  leftFrontDrive.setStopping(hold);
  leftBackDrive.setStopping(hold);
  rightFrontDrive.setStopping(hold);
  rightBackDrive.setStopping(hold);
}

// getters

//gets movement speed based on joystick location and
//converts to voltage evenly
double getLeftSpeedInLinear() {
  double rawSpeed = (getAxis3Pos() + getAxis4Pos());
  return rawSpeed/voltageConverstion;
}

double getRightSpeedInLinear() {
  double rawSpeed = (getAxis3Pos() - getAxis4Pos());
  return rawSpeed/voltageConverstion;
}

//gets movement speed based on joystick location and 
//runs through a quadratic to slew
int getLeftSpeedInSlew() {
  int newVal;
  int rawVal = getAxis3Pos() + getAxis4Pos();
  if(rawVal > 0)
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  else
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  return newVal;
}
int getRightSpeedInSlew() {
  int newVal;
  int rawVal = getAxis3Pos() - getAxis4Pos();
  if(rawVal > 0)
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  else
  {
    newVal = quadraticA * pow(rawVal, powerRatioB);
  }
  return newVal;
}

int getLeftFrontVelocity() {return leftFrontDrive.velocity(rpm);}
int getLeftBackVelocity() {return leftBackDrive.velocity(rpm);}
int getRightFrontVelocity() {return rightFrontDrive.velocity(rpm);}
int getRightBackVelocity() {return rightBackDrive.velocity(rpm);}

double getInertialRotation() { return inert.rotation();}
double getInertialHeading() { return inert.heading();}
double getInertialPitch() {return inert.pitch();}

/*double getVerticalEncoderRotation() { return -1 * verticalTracker.rotation(deg); }
double getHorizontalEncoderRotation() { return -1 * horizontalTracker.rotation(deg); }

double getVerticalEncoderVelocity() { return verticalTracker.velocity(rpm); }
double getHorizontalEncoderVelocity() { return -1 * horizontalTracker.velocity(rpm); }*/

int getLeftFrontTemp() {return leftFrontDrive.temperature(celsius);}
int getLeftBackTemp() {return leftBackDrive.temperature(celsius);}
int getRightFrontTemp() {return rightFrontDrive.temperature(celsius);}
int getRightBackTemp() {return rightBackDrive.temperature(celsius);}

// control

//reset all Motors
void resetDrivetrain() {
  leftFrontDrive.resetRotation();
  leftBackDrive.resetRotation();
  rightFrontDrive.resetRotation();
  rightBackDrive.resetRotation();
}

/*void resetEncoders() {
  verticalTracker.resetRotation();
  horizontalTracker.resetRotation();
}*/

//calibrate inertial sensor for preauton
void calibrateInertial() {
  //inert.calibrate();
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
}

void waitCalibrate(){
  while(inert.isCalibrating()) {
    wait(100, msec);
  }
}

//checks tempeatures of all drive motors are returns in a string which motors are hot
/*std::string tempInfoDrive() {
  std::string tempReturn;
  int loopCounter = 0;
  if (getLeftBackTemp() > tempLimit)
    tempReturn = "LF ";
    loopCounter++;
  if (getLeftMiddleTemp() > tempLimit)
    tempReturn += "LM ";
    loopCounter++;
  if (getLeftBackTemp() > tempLimit)
    tempReturn += "LB ";
    loopCounter++;
  if (getRightFrontTemp() > tempLimit)
    tempReturn += "RF ";
    loopCounter++;
  if (getRightMiddleTemp() > tempLimit)
    tempReturn += "RM ";
    loopCounter++;
  if (getRightBackTemp() > tempLimit)
    tempReturn += "RB ";
    loopCounter++;
  if(loopCounter == 0)
    tempReturn = "All Good";
  return tempReturn;
}*/




//drive movement based on time
void timeDrive(double speed, int timeLength) {
  leftFrontDrive.spin(fwd, speed, volt);
  rightFrontDrive.spin(fwd, speed, volt);
  leftBackDrive.spin(fwd, speed, volt);
  rightBackDrive.spin(fwd, speed, volt);

  wait(timeLength, msec);

  leftFrontDrive.stop();
  rightFrontDrive.stop();
  leftBackDrive.stop();
  rightBackDrive.stop();
}

/*//turn based on different left and right speed to move in a curve
void arcturn (double left, double right, double turnangle) {
  while (getInertialHeading() < turnangle - 2 || getInertialHeading() > turnangle + 2) {
    leftFrontDrive.spin(fwd, left, volt);
    leftMiddleDrive.spin(fwd, left, volt);
    rightFrontDrive.spin(fwd, right, volt);
    rightMiddleDrive.spin(fwd, right, volt);
    wait(10, msec);
  }
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
}

void arcturnTime (double left, double right, int length) {
  leftFrontDrive.spin(fwd, left, volt);
  leftMiddleDrive.spin(fwd, left, volt);
  rightFrontDrive.spin(fwd, right, volt);
  rightMiddleDrive.spin(fwd, right, volt);
  wait(length, msec);
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  leftMiddleDrive.stop();
  rightMiddleDrive.stop();
}*/