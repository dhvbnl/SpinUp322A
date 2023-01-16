#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor leftFrontDrive = motor(PORT14, ratio6_1, true);
motor leftBackDrive = motor(PORT13, ratio6_1, true);

motor rightFrontDrive = motor(PORT19, ratio6_1, false);
motor rightBackDrive = motor(PORT20, ratio6_1, false);

motor flywheel = motor(PORT4, ratio6_1, false);

motor indexer = motor(PORT18, ratio18_1, false);

motor leftIntake = motor(PORT2, ratio6_1, true);
motor rightIntake = motor(PORT10, ratio6_1, true);

inertial inert = inertial(PORT9);

signature BLUEGOAL = signature (1, -3355, -1985, -2670, 8655, 12115, 10385, 5.100, 0);
signature REDGOAL = signature (3, -2759, -2009, -2384, 11045, 12621, 11834, 6.5, 0); //fix

vision v = vision (PORT9, 25, REDGOAL, BLUEGOAL); 

triport bottomExpander = triport(PORT13);
triport topExander = triport(PORT7);

//encoder verticalTracker = encoder(Expander.A);
//encoder horizontalTracker = encoder(Expander.E);

/*digital_out rearClamp = digital_out(bottomExpander.A);  
digital_out frontClamp = digital_out(topExander.F);

digital_out frontClampStandoff = digital_out(topExander.E);
digital_out goalCover = digital_out(topExander.D);

limit rearClampLimit = limit(Brain.ThreeWirePort.C);
limit rearGoalLimit = limit(Brain.ThreeWirePort.G);

pot fourBarPot = pot(bottomExpander.D);

line frontLineTracker = line(Brain.ThreeWirePort.D);
line intakeLineTracker = line(Brain.ThreeWirePort.A);

sonar rearSonar = sonar(bottomExpander.C);*/

void vexcodeInit(void) {
  
}