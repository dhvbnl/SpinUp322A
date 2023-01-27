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

motor indexer = motor(PORT18, ratio18_1, true);

motor leftIntake = motor(PORT2, ratio6_1, true);
motor rightIntake = motor(PORT10, ratio6_1, false);

inertial inert = inertial(PORT17);

//signature BLUEGOAL = signature (1, -4829, -683, -2756, 7021, 15639, 11330, 1.600, 0);
signature BLUEGOAL = signature (1, -3923, 2235, -844, 5783, 14261, 10022, 1.300, 0);
signature REDGOAL = signature (2, 5815, 8417, 7116, 297, 1141, 719, 3.800, 0);

vision v = vision (PORT9, 25, REDGOAL, BLUEGOAL); 

digital_out indexerClamp = digital_out(Brain.ThreeWirePort.A);

digital_out flywheelAdjuster = digital_out(Brain.ThreeWirePort.B);    

line flywheelCheck = line(Brain.ThreeWirePort.C);
line indexerTop = line(Brain.ThreeWirePort.D);


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