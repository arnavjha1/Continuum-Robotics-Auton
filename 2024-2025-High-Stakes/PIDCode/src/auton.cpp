#include <init.h>
#include <subsystems.h>
#include <turnPID.h>
#include <drivePID.h>
#include <auton.h>

using namespace vex;

void auton() {
  Drivetrain.setStopping(brake);

  // drivePID(14.5);
  // turnPID(270);
  drivePID(-80);
  

  Drivetrain.setStopping(coast);
}
