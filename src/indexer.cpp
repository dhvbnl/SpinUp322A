#include "vex.h"

bool indexerOverride = true;

int indexerState = 0;
int indexerDelay = 0;
int indexerSpeed = 0;


void indexerControl() {
  //printf("%ld \n", flywheelAdjuster.value());
  while (true) {
    // set speed based on inputs
    setIndexerSpeed(false, false);
    wait(10, msec);
  }
}

void setIndexerSpeed(bool force, bool up) {
  if (!indexerOverride) {
    //
  } else {
    if (flywheel.velocity(pct) != 0 && getR2Pos()) {
      shootDisc();
    }
  }
}

// clamp - whether or not clamp is in place
// speed - speed of indexer
void indexmanual(double speed, bool clamp) {
  intake.spin(fwd, -speed, volt);
}

// void setindexerClamp() { indexerClamp.set(!indexerClamp.value()); }

void shootDisc(){
  indexerState++;
  wait(15, msec);
  intake.spin(fwd, -12, volt);
  printf("made it");
  int counter = 0;
  while(flywheelCheck.value(pct) > 50 && counter < 30){
    counter++;
    wait(20, msec);
  }
  if(counter < 30){
    //wait(200, msec);
    shootDisc();
  }
  indexerState--;
}

int getIndexerState(){
  return indexerState;
}