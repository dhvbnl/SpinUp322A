#include "vex.h"

// const int centerX = 165;
// const int centerTol = 20;

//home
//const int redBrightness = 29;
//const int blueBrightness = 150;
//const int yellowBrightness = 12;

//comp
const int redBrightness = 39;
const int blueBrightness = 88;

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
    setDrivetrainSpeed(5.0,-5.0);
    printf("right %f \n", 0.0);
  } else {
    setDrivetrainSpeed(-5.0, 5.0);
    printf("left %f \n", 0.0);
  }

  // // if no objects are detected, turn and check again...
  // while (v.objectCount == 0 ||
  //         v.largestObject.height < 10 ||
  //         v.largestObject.width < 20) {
  //   wait(10, msec);
  //   v.takeSnapshot(sig);
  // }
  

  bool objFound = false;
  vision::object test;
  while(!objFound) {
    wait(10, msec);
    int num = v.takeSnapshot(sig);
    if (v.objectCount != 0 && v.largestObject.height > 10 && v.largestObject.width > 10) {
      printf("object found %f \n", 1.0 * num);
      for (int i = 0; i < num; i++) {
        vision::object obj = v.objects[i];
        if (obj.centerY > 40 && obj.centerY < 60) {
          if ((obj.height > 10 && obj.height < 23) && (obj.width > 35 && obj.width < 55)) {
            test = obj;
            objFound = true;
            break;
          }
        }
      }
    }
  }

  setDrivetrainSpeed(0, 0);
  printf("x coordinate %i \n", test.centerX);
  //wait(5000, msec);
  wait(500, msec);

  int lowerCenterXBound = 155; //165
  int upperCenterXBound = 170; //157.5 = exact center

  double leftspeed; 
  double rightspeed; 
  while (test.centerX < lowerCenterXBound || test.centerX > upperCenterXBound) {
    // for (int i = 0; i < v.takeSnapshot(sig); i++) {
    //   vision::object obj = v.objects[i];
    //   if (obj.centerY > 40 && obj.centerY < 60) {
    //     //if ((obj.height > 10 && obj.height < 23) && (obj.width > 35 && obj.width < 55)) {
    //       test = obj;
    //       break;
    //   }
    // }
    v.takeSnapshot(sig);
    test = v.largestObject;
    if (test.centerX < lowerCenterXBound) {
      leftspeed = 2.5;
      rightspeed = -2.5;
      printf("turn right %f \n", double(test.centerX));
    } 
     else if (test.centerX > upperCenterXBound) {
      leftspeed = -2.5; 
      rightspeed = 2.5;
      printf("turn left %f \n", double(test.centerX));
    } else {
      leftspeed = 0;
      rightspeed = 0;
    }
    setDrivetrainSpeed(leftspeed, rightspeed);
    wait(10, msec);
    //v.takeSnapshot(sig);
  }
  
  setDrivetrainSpeed (0, 0);
  area = test.width * test.height;
  printf("finished %f \n", double(test.centerX));
  printf("areavision %f \n", area);
  printf("width %f \n", double(test.width));
  printf("height %f \n", double(test.height));
  return test.width;
}
