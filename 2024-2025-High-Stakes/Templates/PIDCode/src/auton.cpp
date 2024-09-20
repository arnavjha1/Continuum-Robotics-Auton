#include <init.h>
#include <subsystems.h>
#include <turnPID.h>
#include <drivePID.h>
#include <auton.h>

using namespace vex;

void auton() {
  drivePID(-36);
  Controller1.Screen.print(" ");
  Controller1.Screen.print(Brain.Timer.time(seconds));
  Controller1.Screen.print(" ");
  Controller1.Screen.print(InertialSensor.heading(degrees));
}
