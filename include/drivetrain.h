//constants
const double quadraticA = 0.12;
const int powerRatioB = 1;

//complete functions
void drivetrainControl();

void startBalance();

//setters
void setDrivetrainSpeed(double leftSpeed, double rightSpeed);

void expansionRelease();

void setDrivetrainStopping();
void setDrivetrainCreep();
void setDrivetrainLock();
void setDrivetrainHold();

//getters
double getLeftSpeedInLinear();
double getRightSpeedInLinear();

int getLeftSpeedInSlew();
int getRightSpeedInSlew();

int getLeftFrontVelocity();
int getLeftBackVelocity();
int getRightFrontVelocity();
int getRightBackVelocity();

double getInertialRotation();
double getInertialHeading();
double getInertialPitch();

double getVerticalEncoderRotation();
double getHorizontalEncoderRotation();

double getVerticalEncoderVelocity();
double getHorizontalEncoderVelocity();

int getLeftFrontTemp();
int getLeftBackTemp();
int getRightFrontTemp();
int getRightBackTemp();

//control 
void resetDrivetrain();
void resetEncoders();
void calibrateInertial();
void waitCalibrate();
void drivetrainTurn(double targetdeg);
void timeDrive(double speed, int timeLength);
void arcturn (double left, double right, double turnangle);
void arcturnTime (double left, double right, int length);
void drivetrainTurn(double targetdeg);
void arcturn2 (double left, double right, double turnangle);
//std::string tempInfoDrive();

void arcturn (double left, double right, double turnangle);