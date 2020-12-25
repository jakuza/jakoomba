#ifndef Jakoomba_h
#define Jakoomba_h

#include <Automaton.h>
#include "Jakoomba_motor.h"

class Jakoomba: public Machine {

 public:
  enum { IDLE, FORWARD, ESC_RIGHT, ESC_LEFT, TURN_RIGHT, TURN_LEFT }; // STATES
  enum { EVT_START, EVT_HALT, EVT_BUMP_LEFT, EVT_BUMP_RIGHT, EVT_REVERSE_TIMER, EVT_TURN_TIMER, ELSE }; // EVENTS
  Jakoomba(void) : Machine() {};
  Jakoomba& begin(void);
  Jakoomba& trace(Stream & stream);
  Jakoomba& trigger(int event);
  int state(void);
  Jakoomba& onChange(Machine& machine, int event = 0);
  Jakoomba& onChange(atm_cb_push_t callback, int idx = 0);
  Jakoomba& onEscleft(Machine& machine, int event = 0);
  Jakoomba& onEscleft(atm_cb_push_t callback, int idx = 0);
  Jakoomba& onEscright(Machine& machine, int event = 0);
  Jakoomba& onEscright(atm_cb_push_t callback, int idx = 0);
  Jakoomba& onForward(Machine& machine, int event = 0);
  Jakoomba& onForward(atm_cb_push_t callback, int idx = 0);
  Jakoomba& onTurnleft(Machine& machine, int event = 0);
  Jakoomba& onTurnleft(atm_cb_push_t callback, int idx = 0);
  Jakoomba& onTurnright(Machine& machine, int event = 0);
  Jakoomba& onTurnright(atm_cb_push_t callback, int idx = 0);
  Jakoomba& start(void);
  Jakoomba& halt(void);
  Jakoomba& bump_left(void);
  Jakoomba& bump_right(void);

 private:
  enum { ENT_IDLE, ENT_FORWARD, ENT_ESC_RIGHT, ENT_ESC_LEFT, ENT_TURN_RIGHT, ENT_TURN_LEFT }; // ACTIONS
  enum { ON_CHANGE, ON_ESCLEFT, ON_ESCRIGHT, ON_FORWARD, ON_TURNLEFT, ON_TURNRIGHT, CONN_MAX }; // CONNECTORS
  atm_connector connectors[CONN_MAX];
  atm_timer_millis reverse_timer, turn_timer;
  int event(int id); 
  void action(int id);

};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Jakoomba">
    <states>
      <IDLE index="0" sleep="1" on_enter="ENT_IDLE">
        <EVT_START>FORWARD</EVT_START>
      </IDLE>
      <FORWARD index="1" on_enter="ENT_FORWARD">
        <EVT_HALT>IDLE</EVT_HALT>
        <EVT_BUMP_LEFT>ESC_RIGHT</EVT_BUMP_LEFT>
        <EVT_BUMP_RIGHT>ESC_LEFT</EVT_BUMP_RIGHT>
      </FORWARD>
      <ESC_RIGHT index="2" on_enter="ENT_ESC_RIGHT">
        <EVT_HALT>IDLE</EVT_HALT>
        <EVT_REVERSE_TIMER>TURN_RIGHT</EVT_REVERSE_TIMER>
      </ESC_RIGHT>
      <ESC_LEFT index="3" on_enter="ENT_ESC_LEFT">
        <EVT_HALT>IDLE</EVT_HALT>
        <EVT_REVERSE_TIMER>TURN_LEFT</EVT_REVERSE_TIMER>
      </ESC_LEFT>
      <TURN_RIGHT index="4" on_enter="ENT_TURN_RIGHT">
        <EVT_HALT>IDLE</EVT_HALT>
        <EVT_BUMP_RIGHT>ESC_LEFT</EVT_BUMP_RIGHT>
        <EVT_TURN_TIMER>FORWARD</EVT_TURN_TIMER>
      </TURN_RIGHT>
      <TURN_LEFT index="5" on_enter="ENT_TURN_LEFT">
        <EVT_HALT>IDLE</EVT_HALT>
        <EVT_BUMP_LEFT>ESC_RIGHT</EVT_BUMP_LEFT>
        <EVT_TURN_TIMER>FORWARD</EVT_TURN_TIMER>
      </TURN_LEFT>
    </states>
    <events>
      <EVT_START index="0" access="PUBLIC"/>
      <EVT_HALT index="1" access="PUBLIC"/>
      <EVT_BUMP_LEFT index="2" access="PUBLIC"/>
      <EVT_BUMP_RIGHT index="3" access="PUBLIC"/>
      <EVT_REVERSE_TIMER index="4" access="PRIVATE"/>
      <EVT_TURN_TIMER index="5" access="PRIVATE"/>
    </events>
    <connectors>
      <CHANGE autostore="0" broadcast="0" dir="PUSH" slots="1"/>
      <ESCLEFT autostore="0" broadcast="0" dir="PUSH" slots="1"/>
      <ESCRIGHT autostore="0" broadcast="0" dir="PUSH" slots="1"/>
      <FORWARD autostore="0" broadcast="0" dir="PUSH" slots="1"/>
      <TURNLEFT autostore="0" broadcast="0" dir="PUSH" slots="1"/>
      <TURNRIGHT autostore="0" broadcast="0" dir="PUSH" slots="1"/>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

#endif
