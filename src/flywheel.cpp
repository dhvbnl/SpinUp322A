#include "vex.h"

bool flywheelOverride = true;

int flywheelState = 0;
int flywheelDelay = 0;
double flywheelSpeed = 0;

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
        if(angleAdjuster.value() == 1){
          flywheelSpeed = 85;
        } else{
          flywheelSpeed = 100;
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
    if(flywheelSpeed != 0){
      flywheelP(flywheelSpeed);
    } else{
      flywheel.spin(fwd, 0, volt);
    }
    
    //flywheel.spin(fwd, flywheelSpeed, volt);
  }
}

void flywheelmanual(double speed) { flywheel.spin(fwd, speed, pct); }

void flywheelAdjust() {
  if (getL1Pos() && flywheelDelay > 20) {
    angleAdjuster.set(true);
    flywheelDelay = 0;
    flywheelSpeed = 85;
  } else if (getL2Pos() && flywheelDelay > 20) {
    angleAdjuster.set(false);
    flywheelDelay = 0;
    setIndexerSpeed(true, true);
  }
  { flywheelDelay++; }
}

void flywheelP(int percent){
  int currentVelocity = flywheel.velocity(pct);
  int speed = percent / voltageConverstion;

  if(currentVelocity < percent - 1){
    speed += (percent - currentVelocity)/2;
  } else if(currentVelocity > percent + 1){
    speed += (percent - currentVelocity)/2;
  }
    flywheel.spin(fwd, speed, volt);
}
