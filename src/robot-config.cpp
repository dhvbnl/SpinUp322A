#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller = controller(primary);

/* ENTER CORRECT PORTS FOR MOTORS*/
motor leftFrontDrive = motor(PORT13, ratio6_1, true);
motor leftBackDrive = motor(PORT11, ratio6_1, true);
motor leftMiddleDrive = motor(PORT12, ratio6_1, false); 

motor rightFrontDrive = motor(PORT18, ratio6_1, false);
motor rightBackDrive = motor(PORT20, ratio6_1, false);
motor rightMiddleDrive = motor(PORT19, ratio6_1, true);

motor flywheel = motor(PORT7, ratio6_1, false);

// motor indexer = motor(PORT18, ratio18_1, true);

// motor leftIntake = motor(PORT2, ratio6_1, true);
// motor rightIntake = motor(PORT10, ratio6_1, false);

motor intake = motor(PORT21, ratio6_1, false);

inertial inert = inertial(PORT2);

//signature BLUEGOAL = signature (1, -4829, -683, -2756, 7021, 15639, 11330, 1.600, 0);
// signature BLUEGOAL = signature (1, -4097, -929, -2513, 7637, 11285, 9461, 3.800, 0);
// signature REDGOAL = signature (2, 9545, 10547, 10046, -2979, 625, -1177, 10.700, 0);


signature BLUEGOAL (1, -1057, 601, -228, 6731, 7761, 7246, 6.200, 0);
signature REDGOAL (2, 8437, 9919, 9178, -1807, -245, -1026, 4.000, 0);
vision v = vision (PORT10, 25, REDGOAL, BLUEGOAL); 

digital_out angleAdjuster = digital_out(Brain.ThreeWirePort.B);    

digital_out expansion = digital_out(Brain.ThreeWirePort.C);   

line flywheelCheck = line(Brain.ThreeWirePort.A);
line intakeCheck = line(Brain.ThreeWirePort.D);
line indexerTop = line(Brain.ThreeWirePort.E);

//triport bottomExpander = triport(PORT13);
//triport topExander = triport(PORT7);

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