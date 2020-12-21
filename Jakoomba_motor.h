/*
  Jakoomba_motor.h
  Created by Jacopo 'Jakuza' Romei, Dec 21, 2020.
  Released into the public domain.
*/

#ifndef Jakoomba_motor_h
#define Jakoomba_motor_h

#include <Automaton.h>

class Jakoomba_motor: public Machine 
{
  public:
    enum { IDLE, FORWARD, REVERSE }; // STATES
    enum { EVT_FORWARD, EVT_REVERSE, EVT_STOP, ELSE }; // EVENTS
    Jakoomba_motor( void ) : Machine() {};
    Jakoomba_motor& begin(int pins[][2]);
    Jakoomba_motor& trace( Stream & stream );
    Jakoomba_motor& trigger( int event );
    int state( void );
    Jakoomba_motor& onChange( Machine& machine, int event = 0 );
    Jakoomba_motor& onChange( atm_cb_push_t callback, int idx = 0 );
    
    Jakoomba_motor& forward( void );
    Jakoomba_motor& reverse( void );
    Jakoomba_motor& stop( void );
    
    atm_timer_millis timer;

  private:
    enum { ENT_IDLE, ENT_FORWARD, ENT_REVERSE }; // ACTIONS
    enum { ON_CHANGE, CONN_MAX }; // CONNECTORS
    atm_connector connectors[CONN_MAX];
    int event( int id );
    void action( int id );

    void operateMotor(bool motor, bool direction);
    void operateMotors(bool left, bool right);
    void stopMotors(void);

    enum {LEFT_MOTOR, RIGHT_MOTOR};
    enum {MOTOR_FORWARD, MOTOR_REVERSE};        
    
    int motorpins[2][2];


};

#endif
