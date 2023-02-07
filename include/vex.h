/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

#include "controller.h"
#include "drivetrain.h"
#include "opcontrol.h"
#include "intake.h"
#include "flywheel.h"
#include "indexer.h"
#include "vision.h"
#include "mapping.h"
#include "preaution.h"
#include "motionprofile.h"

//convert between velocity and voltage.
const double voltageConverstion = 100/12;

const double convertInches = (2.75 * M_PI) / 360;
const double convertDegrees = 360 / (2.75 * M_PI);

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)