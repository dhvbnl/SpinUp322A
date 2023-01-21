#include "vex.h"

bool flywheelOverride = true;

int flywheelState = 0;
int flywheelDelay = 0;
int flywheelSpeed = 0;

void flywheelControl() {
  while (true) {
    //set speed based on inputs
    setflywheelSpeed();
    wait(10, msec);
  }
}

void setflywheelSpeed() {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(0, 0);
  Controller.Screen.print(flywheel.velocity(pct));
  wait(100, msec);
  if (!flywheelOverride) {
    //
  } else {
    if (getR1Pos() && flywheelDelay > 20) {
      if (flywheelState == 0) {
        flywheelSpeed = 12;
        flywheelState = 1;
      } else if(flywheelState == 1){
        flywheelSpeed = 0;
        flywheelState = 0;
      }
      flywheelDelay = 0;
      flywheel.spin(fwd, flywheelSpeed, volt);
    } else {
      flywheelDelay++;
    }
  }
}

void flywheelmanual(double speed) {
  flywheel.spin(fwd, speed, volt);
}
