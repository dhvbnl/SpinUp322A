#include "vex.h"

bool flywheelOverride = true;

int flywheelState = 0;
int flywheelDelay = 0;
int flywheelSpeed = 0;

void flywheelControl() {
  while (true) {
    // set speed based on inputs
    setflywheelSpeed();
    flywheelAdjust();
    wait(10, msec);
  }
}

void setflywheelSpeed() {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(0, 0);
  Controller.Screen.print(flywheel.velocity(pct));
  if (!flywheelOverride) {
    //
  } else {
    if (getR1Pos() && flywheelDelay > 20) {
      if (flywheelState == 0) {
        if(flywheelAdjuster.value() == 1){
          flywheelSpeed = 6;
        } else{
          flywheelSpeed = 12;
        }
        
        flywheelState = 1;
      } else if (flywheelState == 1) {
        flywheelSpeed = 0;
        flywheelState = 0;
      }
      flywheelDelay = 0;
    } else {
      flywheelDelay++;
    }
    flywheel.spin(fwd, flywheelSpeed, volt);
  }
}

void flywheelmanual(double speed) { flywheel.spin(fwd, speed, volt); }

void flywheelAdjust() {
  if (getL1Pos() && flywheelDelay > 20) {
    flywheelAdjuster.set(true);
    flywheelDelay = 0;
    flywheelSpeed = 6;
  } else if (getL2Pos() && flywheelDelay > 20) {
    flywheelAdjuster.set(false);
    flywheelDelay = 0;
  }
  { flywheelDelay++; }
}
