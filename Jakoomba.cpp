#include "Jakoomba.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Jakoomba& Jakoomba::begin() {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                     ON_ENTER    ON_LOOP  ON_EXIT  EVT_START  EVT_HALT  EVT_BUMP_LEFT  EVT_BUMP_RIGHT  EVT_REVERSE_TIMER  EVT_TURN_TIMER  ELSE */
    /*       IDLE */       ENT_IDLE, ATM_SLEEP,      -1,   FORWARD,       -1,            -1,             -1,                -1,             -1,   -1,
    /*    FORWARD */    ENT_FORWARD,        -1,      -1,        -1,     IDLE,     ESC_RIGHT,       ESC_LEFT,                -1,             -1,   -1,
    /*  ESC_RIGHT */  ENT_ESC_RIGHT,        -1,      -1,        -1,     IDLE,            -1,             -1,        TURN_RIGHT,             -1,   -1,
    /*   ESC_LEFT */   ENT_ESC_LEFT,        -1,      -1,        -1,     IDLE,            -1,             -1,         TURN_LEFT,             -1,   -1,
    /* TURN_RIGHT */ ENT_TURN_RIGHT,        -1,      -1,        -1,     IDLE,            -1,       ESC_LEFT,                -1,        FORWARD,   -1,
    /*  TURN_LEFT */  ENT_TURN_LEFT,        -1,      -1,        -1,     IDLE,     ESC_RIGHT,             -1,                -1,        FORWARD,   -1,
  };
  // clang-format on
  Machine::begin(state_table, ELSE);

  reverse_timer.set(500);
  turn_timer.set(500);

  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Jakoomba::event(int id) {
  switch (id) {
    case EVT_REVERSE_TIMER:
      return reverse_timer.expired(this);
    case EVT_TURN_TIMER:
      return turn_timer.expired(this);
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push(connectors, ON_CHANGE, 0, <v>, <up>);
 *   push(connectors, ON_ESCLEFT, 0, <v>, <up>);
 *   push(connectors, ON_ESCRIGHT, 0, <v>, <up>);
 *   push(connectors, ON_FORWARD, 0, <v>, <up>);
 *   push(connectors, ON_TURNLEFT, 0, <v>, <up>);
 *   push(connectors, ON_TURNRIGHT, 0, <v>, <up>);
 */

void Jakoomba::action(int id) {
  switch (id) {
    case ENT_IDLE:
      return;
    case ENT_FORWARD:
      push(connectors, ON_FORWARD, 0, 0, 0);
      return;
    case ENT_ESC_RIGHT:
      push(connectors, ON_ESCRIGHT, 0, 0, 0);
      return;
    case ENT_ESC_LEFT:
      push(connectors, ON_ESCLEFT, 0, 0, 0);
      return;
    case ENT_TURN_RIGHT:
      push(connectors, ON_TURNRIGHT, 0, 0, 0);
      return;
    case ENT_TURN_LEFT:
      push(connectors, ON_TURNLEFT, 0, 0, 0);
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Jakoomba& Jakoomba::trigger(int event) {
  Machine::trigger(event);
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Jakoomba::state(void) {
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Jakoomba& Jakoomba::start() {
  trigger(EVT_START);
  return *this;
}

Jakoomba& Jakoomba::halt() {
  trigger(EVT_HALT);
  return *this;
}

Jakoomba& Jakoomba::bump_left() {
  trigger(EVT_BUMP_LEFT);
  return *this;
}

Jakoomba& Jakoomba::bump_right() {
  trigger(EVT_BUMP_RIGHT);
  return *this;
}

/*
 * onChange() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onChange(Machine& machine, int event) {
  onPush(connectors, ON_CHANGE, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onChange(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_CHANGE, 0, 1, 1, callback, idx);
  return *this;
}

/*
 * onEscleft() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onEscleft(Machine& machine, int event) {
  onPush(connectors, ON_ESCLEFT, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onEscleft(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_ESCLEFT, 0, 1, 1, callback, idx);
  return *this;
}

/*
 * onEscright() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onEscright(Machine& machine, int event) {
  onPush(connectors, ON_ESCRIGHT, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onEscright(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_ESCRIGHT, 0, 1, 1, callback, idx);
  return *this;
}

/*
 * onForward() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onForward(Machine& machine, int event) {
  onPush(connectors, ON_FORWARD, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onForward(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_FORWARD, 0, 1, 1, callback, idx);
  return *this;
}

/*
 * onTurnleft() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onTurnleft(Machine& machine, int event) {
  onPush(connectors, ON_TURNLEFT, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onTurnleft(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_TURNLEFT, 0, 1, 1, callback, idx);
  return *this;
}

/*
 * onTurnright() push connector variants (slots 1, autostore 0, broadcast 0)
 */

Jakoomba& Jakoomba::onTurnright(Machine& machine, int event) {
  onPush(connectors, ON_TURNRIGHT, 0, 1, 1, machine, event);
  return *this;
}

Jakoomba& Jakoomba::onTurnright(atm_cb_push_t callback, int idx) {
  onPush(connectors, ON_TURNRIGHT, 0, 1, 1, callback, idx);
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Jakoomba& Jakoomba::trace(Stream & stream) {
  Machine::setTrace(&stream, atm_serial_debug::trace,
    "JAKOOMBA\0EVT_START\0EVT_HALT\0EVT_BUMP_LEFT\0EVT_BUMP_RIGHT\0EVT_REVERSE_TIMER\0EVT_TURN_TIMER\0ELSE\0IDLE\0FORWARD\0ESC_RIGHT\0ESC_LEFT\0TURN_RIGHT\0TURN_LEFT");
  return *this;
}
