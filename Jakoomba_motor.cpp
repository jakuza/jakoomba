/*
  Jakoomba_motor.cpp
  Created by Jacopo 'Jakuza' Romei, Dec 21, 2020.
  Released into the public domain.
*/

#include "Jakoomba_motor.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Jakoomba_motor& Jakoomba_motor::begin(int pins[][2]) 
{
  const static state_t state_table[] PROGMEM = {
    /*               ON_ENTER    ON_LOOP  ON_EXIT  EVT_STOP  EVT_RIGHT  EVT_LEFT  EVT_REVERSE  EVT_FORWARD  ELSE */
    /*    IDLE */    ENT_IDLE, ATM_SLEEP,      -1,       -1,     RIGHT,     LEFT,     REVERSE,     FORWARD,   -1,
    /* FORWARD */ ENT_FORWARD,        -1,      -1,     IDLE,     RIGHT,     LEFT,     REVERSE,          -1,   -1,
    /* REVERSE */ ENT_REVERSE,        -1,      -1,     IDLE,     RIGHT,     LEFT,          -1,     FORWARD,   -1,
    /*    LEFT */    ENT_LEFT,        -1,      -1,     IDLE,     RIGHT,       -1,     REVERSE,     FORWARD,   -1,
    /*   RIGHT */   ENT_RIGHT,        -1,      -1,     IDLE,        -1,     LEFT,     REVERSE,     FORWARD,   -1,
  };
  Machine::begin(state_table, ELSE);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      this->motorpins[i][j] = pins[i][j];      
      pinMode(pins[i][j], OUTPUT);
    }
  }

  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Jakoomba_motor::event(int id) 
{
//  switch (id) {
//    case EVT_ESC_TIMER:
//      return _timer.expired(this);
//  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push(connectors, ON_CHANGE, 0, <v>, <up>);
 */

void Jakoomba_motor::action(int id) 
{
  switch (id) {
    case ENT_IDLE:
      stopMotors();
      return;
    case LP_IDLE:
      return;    
    case ENT_FORWARD:
      operateMotors(MOTOR_FORWARD, MOTOR_FORWARD);
      return;
    case ENT_REVERSE:
      operateMotors(MOTOR_REVERSE, MOTOR_REVERSE);
      return;
    case ENT_LEFT:
      operateMotors(MOTOR_REVERSE, MOTOR_FORWARD);
      return;
    case ENT_RIGHT:
      operateMotors(MOTOR_FORWARD, MOTOR_REVERSE);
      return;
  }
}

void Jakoomba_motor::stopMotors() 
{
  digitalWrite(motorpins[LEFT_MOTOR][MOTOR_FORWARD], LOW);
  digitalWrite(motorpins[LEFT_MOTOR][MOTOR_REVERSE], LOW);
  digitalWrite(motorpins[RIGHT_MOTOR][MOTOR_FORWARD], LOW);
  digitalWrite(motorpins[RIGHT_MOTOR][MOTOR_REVERSE], LOW);
}

void Jakoomba_motor::operateMotors(bool left_motor_direction, bool right_motor_direction) 
{
  digitalWrite(motorpins[LEFT_MOTOR][left_motor_direction], HIGH);
  digitalWrite(motorpins[LEFT_MOTOR][!left_motor_direction], LOW);
  digitalWrite(motorpins[RIGHT_MOTOR][right_motor_direction], HIGH);
  digitalWrite(motorpins[RIGHT_MOTOR][!right_motor_direction], LOW);
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Jakoomba_motor& Jakoomba_motor::trigger(int event) 
{
  Machine::trigger(event);
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Jakoomba_motor::state(void) 
{
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Jakoomba_motor& Jakoomba_motor::left() {
  trigger(EVT_LEFT);
  return *this;
}

Jakoomba_motor& Jakoomba_motor::right() {
  trigger(EVT_RIGHT);
  return *this;
}

Jakoomba_motor& Jakoomba_motor::forward() {
  trigger(EVT_FORWARD);
  return *this;
}

Jakoomba_motor& Jakoomba_motor::reverse() {
  trigger(EVT_REVERSE);
  return *this;
}

Jakoomba_motor& Jakoomba_motor::stop() {
  trigger(EVT_STOP);
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Jakoomba_motor& Jakoomba_motor::trace(Stream & stream) 
{
  Machine::setTrace(&stream, atm_serial_debug::trace,
    "MACHINE\0EVT_STOP\0EVT_RIGHT\0EVT_LEFT\0EVT_REVERSE\0EVT_FORWARD\0ELSE\0FORWARD\0REVERSE\0IDLE\0LEFT\0RIGHT");
  return *this;
}
