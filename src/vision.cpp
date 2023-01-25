#include "vex.h"

// const int centerX = 165;
// const int centerTol = 20;

//home
//const int redBrightness = 29;
//const int blueBrightness = 150;
//const int yellowBrightness = 12;

//comp
const int redBrightness = 59;
const int blueBrightness = 50;
//const int yellowBrightness = 25;
// void findFrontGoal(color col, signature sig, int basespeed, bool right,
//                    bool check, bool risk) {
//   if (col == red) {
//     v.setBrightness(redBrightness);
//   } else if (col == blue) {
//     v.setBrightness(blueBrightness);
//   } else if (col == yellow) {
//     v.setBrightness(yellowBrightness);
//   }
//   v.takeSnapshot(sig);
//   if (check) {
//     if (right) {
//       setDrivetrainSpeed(4.5, -4.5);
//     } else {
//       setDrivetrainSpeed(-4.5, 4.5);
//     }
//     while (v.objectCount == 0 ||
//            v.largestObject.height < 10 ||
//            v.largestObject.width < 20) {
//       wait(20, msec);
//       v.takeSnapshot(sig);
//     }
//   }

//   vision::object test = v.largestObject;
//   if (!risk) {
//     while (test.centerX < centerX - centerTol || test.centerX > centerX + centerTol) {
//       if (test.centerX < centerX - centerTol) {
//         setDrivetrainSpeed(-4, 4);
//       } else if (test.centerX > centerX + centerTol) {
//         setDrivetrainSpeed(4, -4);
//       }
//       wait(20, msec);
//       v.takeSnapshot(sig);
//     }
//   }

//   int leftSpeed = basespeed;
//   int rightSpeed = basespeed;
//   while (test.centerY < 140) {
//     if (test.centerY > 120) {
//       basespeed = (140 - test.centerY) / 8 + 3;
//     }
//     if (test.centerY < 165) {
//       if (test.centerX < centerX) {
//         rightSpeed = basespeed;
//         leftSpeed = basespeed + (test.centerX - centerX) * 0.1;
//       } else {
//         leftSpeed = basespeed;
//         rightSpeed = basespeed - (test.centerX - centerX) * 0.1;
//       }
//     } else {
//       leftSpeed = basespeed;
//       rightSpeed = basespeed;
//     }
//     setDrivetrainSpeed(leftSpeed, rightSpeed);
//     wait(20, msec);
//     v.takeSnapshot(sig);
//   }
//   // while (frontLineTracker.value(pct) > 60) {
//   //   setDrivetrainSpeed(3, 3);
//   //   wait(20, msec);
//   // }
//   setDrivetrainSpeed(0, 0);
// }


int findGoal(color col, signature sig, bool right) {
  double area = 0;
  if (col == red) {
    v.setBrightness(redBrightness);
  } 
  else if (col == blue) {
    v.setBrightness(blueBrightness);
    printf("blue %f \n", 0.0);
  } 

  v.takeSnapshot(sig);
  if (right) {
    setDrivetrainSpeed(3.5,-3.5);
    printf("right %f \n", 0.0);
  } else {
    setDrivetrainSpeed(-4.25, 4.25);
    printf("left %f \n", 0.0);
  }
  // if no objects are detected, turn and check again...
  while (v.objectCount == 0 ||
          v.largestObject.height < 10 ||
          v.largestObject.width < 20) {
    wait(10, msec);
    v.takeSnapshot(sig);
  }
  printf("object found %f \n", 0.0);
  vision::object test = v.largestObject;
  int lowerCenterXBound = 173; //165
  int upperCenterXBound = 179;

  double leftspeed; 
  double rightspeed; 
  while (test.centerX < lowerCenterXBound || test.centerX > upperCenterXBound) {
    if (test.centerX < lowerCenterXBound) {
      leftspeed = -2.5;
      rightspeed = 2.5;
      printf("turn right %f \n", double(test.centerX));
    } 
     else if (test.centerX > upperCenterXBound) {
      leftspeed = 2.5; 
      rightspeed = -2.5;
      printf("turn left %f \n", double(test.centerX));
    } else {
      leftspeed = 0;
      rightspeed = 0;
    }
    setDrivetrainSpeed(leftspeed, rightspeed);
    wait(100, msec);
    v.takeSnapshot(sig);
  }
  
  setDrivetrainSpeed (0, 0);
  area = test.width * test.height;
  printf("finished %f \n", double(test.centerX));
  printf("areavision %f \n", area);
  printf("width %f \n", double(test.width));
  printf("height %f \n", double(test.height));
  return test.width;
}
