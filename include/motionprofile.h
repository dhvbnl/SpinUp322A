double getLeftEncoder();
double getRightEncoder();

int movel(double speed, bool fwd);
int mover(double speed, bool fwd);

void accelerate ();
void decelerate ();
void driveProfile(int dist, double maxspeed, bool fwd);
void testmotionprofile(int dist);

