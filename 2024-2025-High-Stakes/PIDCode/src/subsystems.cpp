#include <init.h>
#include <subsystems.h>

using namespace vex;

void spinIntakeForward() {
  Intake.spin(forward);
}
void spinIntakeReverse() {
  Intake.spin(reverse);
}
void stopIntake() {
  Intake.stop();
}

bool mogoPneuPos = false;

void triggerMogoMech() {
  mogoPneuPos = !mogoPneuPos;
  MogoPneu.set(mogoPneuPos);
}

bool intakePneuPos = false;

void triggerIntakePneu() {
  intakePneuPos = !intakePneuPos;
  IntakePneu.set(intakePneuPos);
}

bool hookPneuPos = false;

void triggerHookPneu() {
  hookPneuPos = !hookPneuPos;
  HookPneu.set(hookPneuPos);
}