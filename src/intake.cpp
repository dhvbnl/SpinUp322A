#include "vex.h"

bool intakeState = true;
int intakeDelay = 0;
int discsHeld = 0;

void intakeControl() {
  while (true) {
    // set speed based on inputs
    setIndexerControl();
    //countDisk();
    /*Controller.Screen.clearScreen();
    Controller.Screen.setCursor(0, 0);
    Controller.Screen.print(flywheel.velocity(pct));*/
    //Controller.Screen.newLine();
    //Controller.Screen.print(discsHeld);
    wait(10, msec);
  }
}

void setIntakeSpeed(double speed) {
  if(getIndexerState() == 0){
    intake.spin(fwd, speed, volt);
  }
}

void setIndexerControl() {
  if (intakeState) {
    setIntakeSpeed(getAxis2Pos() / voltageConverstion);
  }
  if(getIndexerState() != 0){
    intakeState = true;
    intakeDelay = 0;
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
  } else if (indexerTop.value(pct) < 55 && intakeState == false) {
    int counter = 0;
    while (counter < 20) {
      wait(20, msec);
      counter++;
    }
    if(indexerTop.value(pct) < 55)
      intakeState = true;
  }else {
    intakeDelay++;
  }
}

/*void countDisk(){
  if(intakeCheck.value(pct) < 60){
    discsHeld += 1;
    wait(100, msec);
  }
  /*if(flywheelCheck.value(pct) < 60){
    while(flywheelCheck.value(pct) < 60){
      wait(20, msec);
    }
    discsHeld -= 1;
  }
}*/