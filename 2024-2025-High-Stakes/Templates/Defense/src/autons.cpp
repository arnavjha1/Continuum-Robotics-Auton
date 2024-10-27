#include "vex.h"
int matchloadangle = 45;
int m = 1;

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
  chassis.drive_settle_error = 3;
}

void ArmPickup(){
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  wait(0.7, seconds);
  Intake.setVelocity(45, percent);/*
  if(m == 1){
    waitUntil(DiscSensor.hue() < 28 || DiscSensor.hue() > 330);
  }
  else{
    waitUntil(DiscSensor.hue() > 180 || DiscSensor.hue() < 250);
  }*/
  wait(0.188, seconds);
  Intake.setVelocity(100, percent);
  Intake.spin(reverse);
  wait(1, seconds);
  Intake.stop();
}

void ArmUp(){
  Arm.spinFor(forward, 400, degrees);
}
void regular(){
  //Pre-auton
  int d = matchloadangle;
  int firstRingAngle = -162;
  double secondRingBite = 33.5;
  
  /*Auton goes here
  ArmPickup();
  
  /*Add arm placement of preload here*/
  chassis.drive_distance(-11);
  chassis.turn_to_angle(-30*m);
  chassis.drive_distance(-13.5);
  MogoPneu.set(true);
  /*Intake.spin(forward);*/
  

  wait(0.2, seconds);
  chassis.turn_to_angle((firstRingAngle+d)*m);
  Intake.spin(forward);
  chassis.drive_distance(16.25);

  chassis.drive_distance(-16.25);
  wait(1.3, seconds);
  chassis.turn_to_angle((firstRingAngle+180+d)*m);
  IntakePneu.set(true);

  chassis.drive_distance(secondRingBite - 5);
  wait(1, seconds);
  IntakePneu.set(false);
  Intake.spin(reverse);

  chassis.drive_distance(5);
  chassis.turn_to_angle(0);
  Intake.spin(forward);
  thread(ArmUp).detach();

  chassis.drive_distance(17.5);
  Arm.spinFor(reverse, 300, degrees);
  chassis.drive_distance(-17.5);
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
  //Pre-auton
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

void tank_odom_test(){
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