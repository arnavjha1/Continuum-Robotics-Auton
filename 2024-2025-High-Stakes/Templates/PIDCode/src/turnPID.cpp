#include <init.h>
#include <turnPID.h>

using namespace vex;

#pragma region FindDist

int dist(int start, int end) {
  start %= 360; end %= 360;
  int rightDist = 0;
  int leftDist = 0;
  if (end < start) {
      rightDist = 360-start+end;
  }
  else {
      rightDist = end-start;
  }
  if (start < end) {
      leftDist = 360-end+start;
  }
  else {
      leftDist = start-end;
  }
  if (leftDist < rightDist) {
      return -1*leftDist;
  }
  return rightDist;
}

#pragma endregion FindDist

#pragma region TurnPID

void turnPID(int finalPos) {
  float kp = 0.30;
  float ki = 0.0;
  float kd = 0.60;

  float integralActiveZone = 10;
  float currentSpeed = 0;
  float totalError;
  float lastError = 0;
  float proportion;
  float integral;
  float derivative;

  Drivetrain.turn(right);

  while (true) {
    float error = dist(InertialSensor.heading(), finalPos);
    if (fabs(error) < 0.5) {
      break;
    }
    if (fabs(error) < integralActiveZone) {
      totalError += fabs(error);
    }
    else {
      totalError = 0;
    }
    if (totalError > 50/ki) {
      totalError = 50/ki;
    }
    proportion = error*kp;
    integral = totalError*ki;
    derivative = (fabs(error)-fabs(lastError))*kd;

    lastError = error;

    currentSpeed = proportion+integral+derivative;

    Drivetrain.setTurnVelocity(currentSpeed, percent);
    wait(5, msec);
  }
  Drivetrain.stop();
}

#pragma endregion TurnPID