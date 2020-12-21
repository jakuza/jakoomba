/*
  Jakoomba_motor.cpp
  Created by Jacopo 'Jakuza' Romei, Dec 21, 2020.
  Released into the public domain.
*/

#include "Jakoomba_motor.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Jakoomba_motor& Jakoomba_motor::begin(int pins[][2], int bump_amplitude) 
{
  const static state_t state_table[] PROGMEM = {
    /*               ON_ENTER  ON_LOOP  ON_EXIT   EVT_TIMER   EVT_FORWARD  EVT_REVERSE   EVT_STOP  ELSE */
    /*    IDLE */    ENT_IDLE,      -1,      -1,         -1,      FORWARD,     REVERSE,        -1,   -1,
    /* FORWARD */ ENT_FORWARD,      -1,      -1,         -1,           -1,     REVERSE,      IDLE,   -1,
    /* REVERSE */ ENT_REVERSE,      -1,      -1,    TURNING,      FORWARD,          -1,      IDLE,   -1,
    /* TURNING */ ENT_TURNING,      -1,      -1,    FORWARD,           -1,          -1,        -1,   -1,
  };
  Machine::begin( state_table, ELSE );

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      this->motorpins[i][j] = pins[i][j];      
      pinMode(pins[i][j], OUTPUT);
    }
  }

  _timer.set(bump_amplitude);
  
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Jakoomba_motor::event( int id ) 
{
  switch ( id ) {
    case EVT_TIMER:
      return _timer.expired(this);
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push( connectors, ON_CHANGE, 0, <v>, <up> );
 */

void Jakoomba_motor::action( int id ) 
{
  switch ( id ) {
    case ENT_IDLE:
      stopMotors();
      return;
    case ENT_FORWARD:
      operateMotors(MOTOR_FORWARD, MOTOR_FORWARD);
      return;
    case ENT_REVERSE:
      operateMotors(MOTOR_REVERSE, MOTOR_REVERSE);
      return;
    case ENT_TURNING:
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

void Jakoomba_motor::operateMotor(bool motor, bool direction) 
{
  digitalWrite(motorpins[motor][direction], HIGH);
  digitalWrite(motorpins[motor][!direction], LOW);
}

void Jakoomba_motor::operateMotors(bool left, bool right) 
{
  digitalWrite(motorpins[LEFT_MOTOR][left], HIGH);
  digitalWrite(motorpins[LEFT_MOTOR][!left], LOW);
  digitalWrite(motorpins[RIGHT_MOTOR][right], HIGH);
  digitalWrite(motorpins[RIGHT_MOTOR][!right], LOW);
}
/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Jakoomba_motor& Jakoomba_motor::trigger( int event ) 
{
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Jakoomba_motor::state( void ) 
{
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Jakoomba_motor& Jakoomba_motor::timer() 
{
  trigger( EVT_TIMER );
  return *this;
}

Jakoomba_motor& Jakoomba_motor::forward() 
{
  trigger( EVT_FORWARD );
  return *this;
}

Jakoomba_motor& Jakoomba_motor::reverse() 
{
  trigger( EVT_REVERSE );
  return *this;
}

Jakoomba_motor& Jakoomba_motor::stop() 
{
  trigger( EVT_STOP );
  return *this;
}

/*
 * onChange() push connector variants ( slots 1, autostore 0, broadcast 0 )
 */

Jakoomba_motor& Jakoomba_motor::onChange( Machine& machine, int event ) 
{
  onPush( connectors, ON_CHANGE, 0, 1, 1, machine, event );
  return *this;
}

Jakoomba_motor& Jakoomba_motor::onChange( atm_cb_push_t callback, int idx ) 
{
  onPush( connectors, ON_CHANGE, 0, 1, 1, callback, idx );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Jakoomba_motor& Jakoomba_motor::trace( Stream & stream ) 
{
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "MOTOR\0EVT_TIMER\0EVT_FORWARD\0EVT_REVERSE\0EVT_STOP\0ELSE\0IDLE\0FORWARD\0REVERSE\0TURNING" );
  return *this;
}
