#include "vex.h"

bool indexerOverride = true;

int indexerState = 0;
int indexerDelay = 0;
int indexerSpeed = 0;

void indexerControl() {
  printf("%ld \n", flywheelAdjuster.value());
  while (true) {
    //set speed based on inputs
    setIndexerSpeed();
    wait(10, msec);
  }
}

void setIndexerSpeed() {
if (!indexerOverride) {
    //
  } else {
    if (getR2Pos() && indexerDelay > 20) {
      printf("activated \n", flywheelAdjuster.value());
      if (indexerState == 0) {
        indexerSpeed = 8;
        indexerState = 1;
        indexerClamp.set(true);
      } else if(indexerState == 1){
        indexerSpeed = 0;
        indexerState = 0;
        indexerClamp.set(false);
      }
      indexerDelay = 0;
      
    } else {
      indexerDelay++;
    }
    if(flywheelAdjuster.value() == 0 && flywheel.isSpinning()){
      if(flywheel.velocity(pct) < 70){
      indexer.spin(fwd, 0, volt);
      int counter = 0;
      while(flywheel.velocity(pct) < 75 && counter > 25){
        counter++;
        wait(20, msec);
      }
    } else{
      indexer.spin(fwd, indexerSpeed, volt);
    }
    } else{
      indexer.spin(fwd, indexerSpeed, volt);
    }
    
    
  }
}

void indexmanual (double speed, bool clamp) {
  indexerClamp.set(clamp);
  indexer.spin(fwd, speed, volt);
}
//void setindexerClamp() { indexerClamp.set(!indexerClamp.value()); }