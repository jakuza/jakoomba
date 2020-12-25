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
    enum { IDLE, FORWARD, REVERSE, LEFT, RIGHT }; // STATES
    enum { EVT_STOP, EVT_RIGHT, EVT_LEFT, EVT_REVERSE, EVT_FORWARD, ELSE }; // EVENTS
    Jakoomba_motor(void) : Machine() {};
    Jakoomba_motor& begin(int pins[][2]);
    Jakoomba_motor& trace(Stream & stream);
    Jakoomba_motor& trigger(int event);
    int state(void);
    
    Jakoomba_motor& left(void);
    Jakoomba_motor& right(void);
    Jakoomba_motor& forward(void);
    Jakoomba_motor& reverse(void);
    Jakoomba_motor& stop(void);
    
  private:
    enum { ENT_FORWARD, ENT_REVERSE, ENT_IDLE, LP_IDLE, ENT_LEFT, ENT_RIGHT }; // ACTIONS
    int event(int id);
    void action(int id);

    enum {LEFT_MOTOR, RIGHT_MOTOR};
    enum {MOTOR_FORWARD, MOTOR_REVERSE};        

    int motorpins[2][2];
    
    void operateMotor(bool motor, bool direction);
    void operateMotors(bool left, bool right);
    void stopMotors(void);    
};

/* 
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_machine">
    <states>
      <FORWARD index="0" on_enter="ENT_FORWARD">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_RIGHT>RIGHT</EVT_RIGHT>
        <EVT_LEFT>LEFT</EVT_LEFT>
        <EVT_REVERSE>REVERSE</EVT_REVERSE>
      </FORWARD>
      <REVERSE index="1" on_enter="ENT_REVERSE">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_RIGHT>RIGHT</EVT_RIGHT>
        <EVT_LEFT>LEFT</EVT_LEFT>
        <EVT_FORWARD>FORWARD</EVT_FORWARD>
      </REVERSE>
      <IDLE index="2" sleep="1" on_enter="ENT_IDLE" on_loop="LP_IDLE">
        <EVT_RIGHT>RIGHT</EVT_RIGHT>
        <EVT_LEFT>LEFT</EVT_LEFT>
        <EVT_REVERSE>REVERSE</EVT_REVERSE>
        <EVT_FORWARD>FORWARD</EVT_FORWARD>
      </IDLE>
      <LEFT index="3" on_enter="ENT_LEFT">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_RIGHT>RIGHT</EVT_RIGHT>
        <EVT_REVERSE>REVERSE</EVT_REVERSE>
        <EVT_FORWARD>FORWARD</EVT_FORWARD>
      </LEFT>
      <RIGHT index="4" on_enter="ENT_RIGHT">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_LEFT>LEFT</EVT_LEFT>
        <EVT_REVERSE>REVERSE</EVT_REVERSE>
        <EVT_FORWARD>FORWARD</EVT_FORWARD>
      </RIGHT>
    </states>
    <events>
      <EVT_STOP index="0" access="PUBLIC"/>
      <EVT_RIGHT index="1" access="PUBLIC"/>
      <EVT_LEFT index="2" access="PUBLIC"/>
      <EVT_REVERSE index="3" access="PUBLIC"/>
      <EVT_FORWARD index="4" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end 
*/

#endif
