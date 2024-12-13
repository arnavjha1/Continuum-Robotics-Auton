#include "vex.h"
int matchloadangle = 45;
int m = 1;

void alter(){
  m = 0 - m;
  if(m < 0){
    controller(primary).Screen.setCursor(0, 0);
    controller(primary).Screen.print("Blue - Mirrored");
  }
  else{
    controller(primary).Screen.setCursor(0, 0);
    controller(primary).Screen.print("Red - Regulated");
  }
}

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(0.3, 300, 1000);
  chassis.set_turn_exit_conditions(1, 300, 1800);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 0;
}

void RedStake(){
  Arm.spinFor(forward, 175, degrees);
}

void ArmPickup(){/*
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  wait(0.7, seconds);
  Intake.setVelocity(45, percent);/*
  if(m == 1){
    waitUntil(DiscSensor.hue() < 28 || DiscSensor.hue() > 330);
  }
  else{
    waitUntil(DiscSensor.hue() > 180 || DiscSensor.hue() < 250);
  }*//*
  wait(0.188, seconds);
  Intake.setVelocity(100, percent);
  Intake.spin(reverse);
  wait(1, seconds);
  Intake.stop();*/
  Arm.spinFor(reverse, 100, degrees);
}
void ArmDown(){
  MogoPneu.set(true);
}
void ArmUp(){
  chassis.left_swing_to_angle(3.5);
}
void regular(){
  thread(ArmUp).detach();
  Arm.spinFor(reverse, 325, degrees);
  chassis.drive_distance(10.5);
  thread(RedStake).detach();

  chassis.set_swing_exit_conditions(1, 300, 300);
  chassis.left_swing_to_angle(-4.5);
  chassis.set_swing_exit_conditions(1, 300, 1000);
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);

  chassis.drive_distance(-36);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  
  chassis.set_drive_exit_conditions(0.3, 0, 1000);
  chassis.turn_to_angle(-136 + 4);
  Intake.spin(forward);

  chassis.drive_distance(24);
  wait(0.4, seconds);
  chassis.turn_to_angle(30);
  chassis.drive_distance(33);

  //Doinker down
  chassis.turn_to_angle(76.75);
  //Doinker up
  chassis.turn_to_angle(65);

  Intake.spin(forward);
  chassis.drive_distance(11.5 + 24, 60);
  Intake.stop();
  MogoPneu.set(false);

  chassis.turn_to_angle(-30);
  chassis.set_drive_constants(11, 0.4, 0, 10, 0);
  chassis.drive_distance(-13.75);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  MogoPneu.set(true);
  chassis.turn_to_angle(60);
  
  Intake.spin(forward);
  chassis.drive_distance(19);
  thread(ArmPickup).detach();
  chassis.turn_to_angle(205);
  chassis.drive_distance(18);
  /*
  Arm.spinFor(reverse, 100, degrees);
  chassis.left_swing_to_angle(105);
  chassis.drive_distance(25);

  /*
  chassis.drive_distance(-12.5-7.5);
  
  chassis.left_swing_to_angle(-30);
  chassis.right_swing_to_angle(0);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-8);
  /*chassis.drive_distance(-8.75);
  chassis.turn_to_angle(0);
  chassis.drive_distance(-7-1.5);

  MogoPneu.set(true);
  wait(0.4, seconds);
  chassis.turn_to_angle(-131);
  Intake.spin(forward);

  double resist = 4.0;
  chassis.drive_distance(27 - resist);
  wait(0.6, seconds);
  chassis.drive_distance(11 - 27 + resist);

  chassis.turn_to_angle(105);
  chassis.drive_distance(20);

  
  /*wait(0.3, seconds);
  chassis.turn_to_angle(-190);
  Intake.spin(forward);

  double firstRingDist = 21.75 - 4;
  chassis.drive_distance(firstRingDist);
  chassis.drive_distance(11 - firstRingDist);
  chassis.turn_to_angle(105);

  chassis.drive_distance(24 - 7.5);
  /*Pre-auton
  int d = matchloadangle;
  double firstMogoError = 0.0825;
  int firstRingAngle = -112;
  double secondRingBite = 50.375+7.5;
  double secondRingResist = 18;

  /*Auton goes here
  ArmPickup();
  
  /*Add arm placement of preload here
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  thread(ArmUp).detach();
  chassis.drive_distance(-10+firstMogoError*1.73205081);
  chassis.turn_to_angle(-30*m);
  chassis.set_drive_exit_conditions(0.2, 0, 1000);

  chassis.drive_distance(-14-firstMogoError*2);
  MogoPneu.set(true);
  chassis.set_drive_exit_conditions(0.3, 300, 1000);
  Intake.spin(forward);

  wait(0.6, seconds);
  chassis.turn_to_angle(firstRingAngle*m);
  chassis.drive_distance(16.25);
  wait(1, seconds);

  chassis.turn_to_angle(63.5*m);
  IntakePneu.set(true);
  Intake.spin(forward);
  chassis.drive_distance(secondRingBite - secondRingResist);

  wait(1, seconds);
  chassis.drive_distance(secondRingResist - secondRingBite + 13);
  chassis.turn_to_angle(135*m);
  chassis.drive_distance(20);
  /*thread(ArmDown).detach();
  wait(1, seconds);
  chassis.right_swing_to_angle(0);

  thread(ArmUp).detach();
  wait(1, seconds);
  chassis.drive_distance(3);
  Arm.spinFor(forward, 400, degrees);
  chassis.drive_distance(-17.5);  /*
  chassis.turn_to_angle(45);

  chassis.drive_distance(-secondRingBite + 12.5);
  chassis.turn_to_angle((90+d)*m);
  chassis.drive_distance(24);
  ArmUp();

  /*chassis.drive_distance(-8, 0+d);
  chassis.set_drive_constants(11, 0.7, 0, 10, 0);
  chassis.turn_to_angle(-30+d);  
  chassis.drive_distance(-16.5, 3-30+d);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0); 
  MogoPneu.set(true);

  wait(0.3, seconds);
  Intake.spin(forward);
  chassis.left_swing_to_angle(-93.5+d);
  chassis.drive_distance(24);

  chassis.turn_to_angle(67.5+d);
  Claw.set(true);
  chassis.set_drive_exit_conditions(1.5, 300, 817);
  chassis.drive_distance(61.8);
  wait(0.3, seconds);
  MogoPneu.set(false);

  chassis.turn_to_angle(180+d);
  chassis.set_drive_constants(11, 0.7, 0, 10, 0);  
  chassis.drive_distance(-22);/**/
}

void mirrored(){
  /*Pre-auton
  int d = matchloadangle;
  
  //Auton goes here
  m = -1;
  regular();

  /*chassis.set_heading_constants(6, .21, 0, 1, 0);
  chassis.set_drive_exit_conditions(2, 300, 1000);
  chassis.drive_distance(-44, -30);

  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);

  Intake.spin(forward);
  chassis.turn_to_angle(26.5);
  chassis.drive_distance(16.35);
  MogoPneu.set(false);

  chassis.turn_to_angle(-90);
  Intake.stop();
  chassis.drive_distance(-15.75);
  MogoPneu.set(true);

  wait(0.3, seconds);
  chassis.turn_to_angle(47);
  Claw.set(true);
  Intake.spin(forward);

  chassis.drive_distance(40, 47);
  chassis.drive_distance(-5, 47);
  MogoPneu.set(false);
  */ 
}

void macroArm(){
  while (true) {
    if (DistSensor.objectDistance(inches) < 1) {
      Intake.spinFor(reverse, 10, turns);
      break;
    }
    else  {
      Intake.spin(forward);
    }

    wait(0.02, seconds);
  }
}

//The following codes are test codes, avoid editing!
void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void reglar/*tank_odom_test*/(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}