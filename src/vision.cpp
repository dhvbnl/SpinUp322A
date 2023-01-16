#include "vex.h"

const int centerX = 165;
const int centerTol = 20;

//home
//const int redBrightness = 29;
//const int blueBrightness = 150;
//const int yellowBrightness = 12;

//comp
const int redBrightness = 50;
const int blueBrightness = 100;
const int yellowBrightness = 25;
void findFrontGoal(color col, signature sig, int basespeed, bool right,
                   bool check, bool risk) {
  if (col == red) {
    v.setBrightness(redBrightness);
  } else if (col == blue) {
    v.setBrightness(blueBrightness);
  } else if (col == yellow) {
    v.setBrightness(yellowBrightness);
  }
  v.takeSnapshot(sig);
  if (check) {
    if (right) {
      setDrivetrainSpeed(4.5, -4.5);
    } else {
      setDrivetrainSpeed(-4.5, 4.5);
    }
    while (v.objectCount == 0 ||
           v.largestObject.height < 10 ||
           v.largestObject.width < 20) {
      wait(20, msec);
      v.takeSnapshot(sig);
    }
  }

  vision::object test = v.largestObject;
  if (!risk) {
    while (test.centerX < centerX - centerTol || test.centerX > centerX + centerTol) {
      if (test.centerX < centerX - centerTol) {
        setDrivetrainSpeed(-4, 4);
      } else if (test.centerX > centerX + centerTol) {
        setDrivetrainSpeed(4, -4);
      }
      wait(20, msec);
      v.takeSnapshot(sig);
    }
  }

  int leftSpeed = basespeed;
  int rightSpeed = basespeed;
  while (test.centerY < 140) {
    if (test.centerY > 120) {
      basespeed = (140 - test.centerY) / 8 + 3;
    }
    if (test.centerY < 165) {
      if (test.centerX < centerX) {
        rightSpeed = basespeed;
        leftSpeed = basespeed + (test.centerX - centerX) * 0.1;
      } else {
        leftSpeed = basespeed;
        rightSpeed = basespeed - (test.centerX - centerX) * 0.1;
      }
    } else {
      leftSpeed = basespeed;
      rightSpeed = basespeed;
    }
    setDrivetrainSpeed(leftSpeed, rightSpeed);
    wait(20, msec);
    v.takeSnapshot(sig);
  }
  // while (frontLineTracker.value(pct) > 60) {
  //   setDrivetrainSpeed(3, 3);
  //   wait(20, msec);
  // }
  setDrivetrainSpeed(0, 0);
}


void findGoal(color col, signature sig, int basespeed, bool right) {
  if (col == red) {
    v.setBrightness(redBrightness);
  } 
  else if (col == blue) {
    v.setBrightness(blueBrightness);
  } 

  v.takeSnapshot(sig);
  if (right) {
    setDrivetrainSpeed(4.5, -4.5);
  } else {
    setDrivetrainSpeed(-4.5, 4.5);
  }
  // if no objects are detected, turn and check again...
  while (v.objectCount == 0 ||
          v.largestObject.height < 10 ||
          v.largestObject.width < 20) {
    wait(20, msec);
    v.takeSnapshot(sig);
  }

  vision::object test = v.largestObject;
  int leftSpeed = basespeed;
  int rightSpeed = basespeed;
  int lowerCenterXBound = 154;
  int upperCenterXBound = 160;

  while (test.centerX < lowerCenterXBound || test.centerX > upperCenterXBound) {
    if (test.centerX < lowerCenterXBound) {
        
    } 
    else if (test.centerX > upperCenterXBound) {

    }



    if (test.centerY > 120) {
      basespeed = (140 - test.centerY) / 8 + 3;
    }
    if (test.centerY < 165) {
      if (test.centerX < centerX) {
        rightSpeed = basespeed;
        leftSpeed = basespeed + (test.centerX - centerX) * 0.1;
      } else {
        leftSpeed = basespeed;
        rightSpeed = basespeed - (test.centerX - centerX) * 0.1;
      }
    } else {
      leftSpeed = basespeed;
      rightSpeed = basespeed;
    }
  }
}
