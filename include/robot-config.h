using namespace vex;

extern brain Brain;

using signature = vision::signature;

extern controller Controller;

//main drive motors
extern motor leftFrontDrive;
extern motor rightFrontDrive;
extern motor leftBackDrive;
extern motor rightBackDrive;

//intake/dr4b shared motor
extern motor leftIntake;
extern motor rightIntake;

//intake 
extern motor flywheel;

//goal rotator
extern motor indexer;

//sensors
extern inertial inert;

//vision
extern vision v;
extern signature BLUEGOAL;
extern signature REDGOAL;


extern triport bExpander;

//extern encoder verticalTracker;
//extern encoder horizontalTracker;

/*extern digital_out rearClamp;
extern digital_out frontClamp;
extern digital_out frontClampStandoff;
extern digital_out goalCover;

extern limit rearClampLimit;
extern limit rearGoalLimit;

extern pot fourBarPot;

extern line frontLineTracker;
extern line intakeLineTracker;

extern sonar rearSonar;*/

void vexcodeInit(void);
