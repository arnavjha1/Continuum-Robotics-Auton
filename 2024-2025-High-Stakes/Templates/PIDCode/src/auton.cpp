#include <init.h>
#include <subsystems.h>
#include <turnPID.h>
#include <auton.h>

using namespace vex;

void auton() {
  Brain.Timer.clear();
  turnPID(180);
  Controller1.Screen.print(Brain.Timer.time(seconds));
  Controller1.Screen.print(InertialSensor.heading(degrees));
}
