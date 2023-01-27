#include "vex.h"

bool intakeState = true;
int intakeDelay = 0;

void intakeControl() {
  while (true) {
    // set speed based on inputs
    setIndexerControl();
    wait(10, msec);
  }
}

void setIntakeSpeed(double speed) {
  leftIntake.spin(fwd, speed, volt);
  rightIntake.spin(fwd, speed, volt);
}

void setIndexerControl() {
  if (intakeState) {
    setIntakeSpeed(getAxis2Pos() / voltageConverstion);
  }
  if (getXPos() && intakeDelay > 20) {
    setIntakeSpeed(12);
    intakeState = false;
  } else if (getAPos() && intakeDelay > 20) {
    setIntakeSpeed(-6);
    intakeState = false;
  } else if (getBPos() && intakeDelay > 20) {
    setIntakeSpeed(0);
    intakeState = false;
  } else if (getAxis2Pos() != 0 && intakeState == false) {
    intakeState = true;
  } else if (indexerTop.value(pct) < 50 && intakeState == false) {
    int counter = 0;
    while (counter < 40) {
      wait(20, msec);
      counter++;
    }
    if(indexerTop.value(pct) < 50)
      intakeState = true;
  } else {
    intakeDelay++;
  }
}