#include "vex.h"

void intakeControl() {
  while (true) {
    //set speed based on inputs
    setIntakeSpeed(getAxis2Pos()/voltageConverstion);
    wait(10, msec);
  }
}

void setIntakeSpeed(double speed) {
  leftIntake.spin(fwd, speed, volt);
  rightIntake.spin(fwd, speed, volt);
}