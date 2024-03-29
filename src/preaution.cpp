#include "vex.h"

void preauton() {
  vexcodeInit();
  //set cylinder postion
  //frontVision.setLedColor(0, 0, 0);
  //rearVision.setLedColor(0, 0, 0);
  //frontClampStandoff.set(1);
  //rearClamp.set(1);
  //frontClamp.set(0);

  //reset all sensors
  resetDrivetrain();
  //resetEncoders();

  //set motor stopping type
  setDrivetrainCreep();

  //calibrate inertial sensor
  inert.calibrate();
  while(inert.isCalibrating()) {
    wait(100, msec);
  }

  Controller.Screen.print("preauton");
  //frontVision.setLedColor(0, 255, 0);
  //rearVision.setLedColor(0, 255, 0);
  //Controller.Screen.print("Preauton Complete");
 // thread controllerScreen(screenGUI);
}