#include "Jakoomba.h"

Jakoomba robot;
Jakoomba_motor motor;
Atm_button bumper_left, bumper_right;


void setup() {

  Serial.begin( 9600 );
  motor.trace( Serial );

  int motorpins[2][2] = {
    {21, 14},
    {4, 5},
  };

  motor.begin(motorpins);

  robot.begin()
    .onForward(motor, motor.EVT_FORWARD)
    .onEscleft(motor, motor.EVT_REVERSE)
    .onEscright(motor, motor.EVT_REVERSE)
    .onTurnleft(motor, motor.EVT_LEFT)
    .onTurnright(motor, motor.EVT_RIGHT);
  
  bumper_left.begin(12)
    .onPress(robot, robot.EVT_BUMP_LEFT);  
  bumper_right.begin(11)
    .onPress(robot, robot.EVT_BUMP_RIGHT);

  robot.start();
}

void loop() {
  automaton.run();
}
