#include "Jakoomba.h"

Jakoomba robot;
Jakoomba_motor motor;
Atm_button bumper_left, bumper_right;

struct {
    int motors[2][2];
    int bumpers[2];
} pin {
  {
    {21, 14},
    {4, 5},
  },
  {11, 12}
};

void setup() {

  Serial.begin(9600);
  motor.trace(Serial);

  motor.begin(pin.motors);

  robot.begin()
    .onForward(motor, motor.EVT_FORWARD)
    .onEscleft(motor, motor.EVT_REVERSE)
    .onEscright(motor, motor.EVT_REVERSE)
    .onTurnleft(motor, motor.EVT_LEFT)
    .onTurnright(motor, motor.EVT_RIGHT);
  
  bumper_left.begin(pin.bumpers[0])
    .onPress(robot, robot.EVT_BUMP_LEFT);  
  bumper_right.begin(pin.bumpers[1])
    .onPress(robot, robot.EVT_BUMP_RIGHT);

  robot.start();
}

void loop() {
  automaton.run();
}
