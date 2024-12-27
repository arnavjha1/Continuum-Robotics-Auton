#include "vex.h"
int matchloadangle = 0;
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
  chassis.set_turn_exit_conditions(1, 100, 1000);
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

void ArmPickup(){
  /*
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
  double d = matchloadangle;
  float shift = 1.25;
  /*
  chassis.drive_distance(-14);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(-12);
  chassis.point(0, 0);
  chassis.turn_to_angle(0);
  
  
  chassis.turn_to_angle(90);
  chassis.drive_distance(24, 90);  
  */
  chassis.drive_distance(-34.5 + shift*1.73205081); //(0, -34.5)
  chassis.turn_to_angle(-30);
  chassis.drive_distance(-13.5 - shift*2); 
  thread(ArmDown).detach(); 

  chassis.drive_distance(-2); //(7.75, -47.9233938)
  Intake.spin(forward);
  wait(0.2, seconds);
  chassis.turn_to_angle(11); 
  chassis.drive_distance(13); //(10.2305169, -35.1622404)

  chassis.turn_to_angle(62.5);//46.7933351);
  chassis.drive_distance(41.625 + 10);//45.1130854);//(46.25, -8)
  DoinkerPneu.set(true);
  wait(0.4, seconds);

  chassis.turn_to_angle(98);
  chassis.turn_to_angle(90);
  DoinkerPneu.set(false);
  Intake.spin(forward);

  chassis.drive_distance(13.5);
  chassis.drive_distance(-39 - 1.75);
  chassis.turn_to_angle(-40);
  chassis.drive_distance(24);
  /*
  chassis.drive_distance(-22.25 - 18 - 2);
  Intake.stop();
  chassis.set_turn_constants(12, .4, .03, 3, 15);

  chassis.turn_to_angle(-45);
  chassis.drive_distance(36);
 
  /**//*
  d = 27.5;

  DoinkerPneu.set(true);
  chassis.drive_distance(2);
  chassis.turn_to_angle(90);
  DoinkerPneu.set(false);

  chassis.turn_to_angle(-15);
  Intake.spin(forward);
  chassis.drive_distance(5);


  /*
  Intake.spin(forward);
  chassis.drive_distance(5);
  
  /*
  thread(ArmUp).detach();

  Arm.spinFor(reverse, 325, degrees);
  chassis.drive_distance(10.5);
  Arm.spinFor(forward, 175, degrees);
  chassis.left_swing_to_angle(-4.5);

  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(-36);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();

  chassis.drive_distance(-2);
  chassis.set_drive_exit_conditions(0.3, 0, 1000);
  chassis.turn_to_angle(-134.5);
  Intake.spin(forward);

  chassis.drive_distance(28.75 - 7.5);
  wait(0.4, seconds);
  chassis.turn_to_angle(151.5 - 120);
  chassis.drive_distance(45.875 - 12);

  DoinkerPneu.set(true);
  chassis.turn_to_angle(60);
  DoinkerPneu.set(false);

  chassis.drive_distance(24 + 9.25 + 11);
  MogoPneu.set(false);
  chassis.turn_to_angle(0);
  chassis.drive_distance(10.5);
  
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(-22.25);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();

  chassis.drive_distance(-2);
  thread(ArmPickup).detach();
  wait(0.3, seconds);
  chassis.turn_to_angle(180);

  chassis.drive_distance(15);
  /**//*
  d = 65;
  MogoPneu.set(true);
  wait(1, seconds);

  Intake.spin(forward);
  chassis.drive_distance(35.5);
  Intake.stop();
  MogoPneu.set(false);

  chassis.turn_to_angle(-30 - d);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-11.875);
  MogoPneu.set(true);

  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.turn_to_angle(60 - d);
  Intake.spin(forward);
  chassis.drive_distance(20);

  thread(ArmPickup).detach();
  chassis.turn_to_angle(60 + 159 - d);
  chassis.drive_distance(17.5);
  Intake.stop();/**/
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