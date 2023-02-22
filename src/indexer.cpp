#include "vex.h"

bool indexerOverride = true;

int indexerState = 0;
int indexerDelay = 0;
int indexerSpeed = 0;

// void indexerControl() {
//   printf("%ld \n", flywheelAdjuster.value());
//   while (true) {
//     // set speed based on inputs
//     setIndexerSpeed(false, false);
//     wait(10, msec);
//   }
// }

// void setIndexerSpeed(bool force, bool up) {
//   if (!indexerOverride) {
//     //
//   } else {
//     if ((getR2Pos() && indexerDelay > 20) || force) {
//       printf("activated \n", flywheelAdjuster.value());
//       if(force){
//         if(up){
//           indexerSpeed = 0;
//         indexerState = 0;
//         indexerClamp.set(false);
//         } else{
//           indexerSpeed = 12;
//         indexerState = 1;
//         indexerClamp.set(true);
//         }
//       } else if (indexerState == 0) {
//         indexerSpeed = 12;
//         indexerState = 1;
//         indexerClamp.set(true);
//       } else if (indexerState == 1) {
//         indexerSpeed = 0;
//         indexerState = 0;
//         indexerClamp.set(false);
//       }
//       indexerDelay = 0;

//     } else {
//       indexerDelay++;
//     }

//     if (flywheel.velocity(pct) != 0) {
//       if (flywheelCheck.value(pct) < 40) {
//         //wait(25, msec);
//         indexer.stop(brake);
//         int counter = 0;
//         while (flywheelCheck.value(pct) < 40) {
//           counter++;
//           wait(20, msec);
//         }
//         wait(500, msec);
//       } else {
//         indexer.spin(fwd, indexerSpeed, volt);
//       }
//     } else {
//       indexer.spin(fwd, indexerSpeed, volt);
//     }
//   }
//}

// clamp - whether or not clamp is in place
// speed - speed of indexer
void indexmanual(double speed, bool clamp) {
  intake.spin(fwd, -speed, volt);
}

// void setindexerClamp() { indexerClamp.set(!indexerClamp.value()); }