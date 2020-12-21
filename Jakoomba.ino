#include "Jakoomba_motor.h"

// Basic Arduino sketch - instantiates the state machine and nothing else

Jakoomba_motor motor;
Atm_button button1, button2, button3;

void setup() {

  Serial.begin( 9600 );
  motor.trace( Serial );

  int motorpins[2][2] = {
    {2, 3},
    {4, 5},
  };

  motor.begin(motorpins, 1000);
  motor.trigger(motor.EVT_FORWARD);
  
  button1.begin(12)
    .onPress(motor, motor.EVT_FORWARD);  
  button2.begin(11)
    .onPress(motor, motor.EVT_REVERSE);
  button3.begin(10)
    .onPress(motor, motor.EVT_STOP);
  
}

void loop() {
  automaton.run();
}
