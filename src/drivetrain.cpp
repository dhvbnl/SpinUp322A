#include "vex.h"

int stopTimer = 0;
bool expansionReady = false;

//thread for drivetrain to respond to joystick movements
void drivetrainControl() {
  while (true) {
    //set speed based on inputs
    setDrivetrainSpeed(getLeftSpeedInLinear(), getRightSpeedInLinear());
    expansionRelease();
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

void expansionRelease() {
  if (getUpPos() || expansionReady == true) {
    expansionReady = true;
    if(getRightPos()){
      expansion.set(!expansion.value());
      wait(200, msec);
    }
  }
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

void drivetrainTurn(double targetdeg) {

  double kP = .9; //.9
  double kI = 0.000;
  double kD = 0.25; //.25

  // PID loop variables
  double error = 0.0;
  double integral = 0.0;
  double derivative = 0.0;
  double prevError = 0.0;
  double motorPower = 0.0;
  bool useright = true;
  double avgvel = 0;
  double speed;
  const double minMotorPower = 2.5;
  double changevel = 2.5;
  int x = 0;
  while (fabs(targetdeg - getInertialHeading()) > 1) {
    // PID loop to determine motorPower at any given point in time
    x++;
    avgvel = (fabs(leftFrontDrive.velocity(pct)) + fabs(rightFrontDrive.velocity(pct))) / 2;
    
    double head = getInertialHeading();
    // printf("head %f \n", head);

    double errorright = targetdeg - head;
    if (targetdeg < head) {
      errorright = 360 - head + targetdeg;
    }

    double errorleft = fabs(targetdeg - head);
    if (targetdeg > head) {
      errorleft = 360 + head - targetdeg;
    }

    if (errorright < errorleft) {
      error = errorright;
      useright = true;
    } else {
      error = errorleft;
      useright = false;
    }

    // pid stuff
    
    integral = integral + error;
    if ((error == 0.0) or (error > targetdeg)) {
      integral = 0.0;
    }
    derivative = error - prevError;
    
    speed = (error * kP + integral * kI + derivative * kD);
    motorPower = speed;
    if (avgvel < speed) {
      motorPower += (speed - avgvel) * changevel;
    } else if (avgvel > speed) {
      motorPower -= (avgvel - speed) * changevel;
    } 

    motorPower = motorPower * 12/100;
    prevError = error;

    if (motorPower < minMotorPower) {
      motorPower = minMotorPower;
    }
    setDrivetrainHold();
  
    // powering the motors
    if (!useright) {
      leftFrontDrive.spin(fwd, -motorPower, volt);
      leftBackDrive.spin(fwd, -motorPower, volt);
      rightFrontDrive.spin(fwd, motorPower, volt);
      rightBackDrive.spin(fwd, motorPower, volt);
    } else {
      leftFrontDrive.spin(fwd, motorPower, volt);
      leftBackDrive.spin(fwd, motorPower, volt);
      rightFrontDrive.spin(fwd, -motorPower, volt);
      rightBackDrive.spin(fwd, -motorPower, volt);
    }
    wait(10, msec);

  } // end while()
  leftFrontDrive.stop();
  rightFrontDrive.stop();
  rightBackDrive.stop();
  leftBackDrive.stop();
  
}



