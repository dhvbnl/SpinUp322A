#include "vex.h"

bool indexerOverride = true;

int indexerState = 0;
int indexerDelay = 0;
int indexerSpeed = 0;

void indexerControl() {
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
    if (getL1Pos() && indexerDelay > 20) {
      if (indexerState == 0) {
        indexerSpeed = 12;
        indexerState = 1;
      } else if(indexerState == 1){
        indexerSpeed = 0;
        indexerState = 0;
      }
      indexerDelay = 0;
      
    } else {
      indexerDelay++;
    }
    if(flywheel.velocity(pct) < 70){
      indexer.spin(fwd, 0, volt);
      wait(1, sec);
    } else{
      indexer.spin(fwd, indexerSpeed, volt);
    }
    
  }
}

//void setindexerClamp() { indexerClamp.set(!indexerClamp.value()); }