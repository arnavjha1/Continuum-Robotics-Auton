#include <init.h>
#include <preAuton.h>
#include <userControl.h>
#include <auton.h>
#include "drivePID.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.drivercontrol(userControl);
  Competition.autonomous(auton);

  // Run the pre-autonomous function.
  preAuton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}