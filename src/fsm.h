#ifndef FSM_H
#define FSM_H

#include <iostream>
#include <stdint.h>

#include "queue.h"

enum TriggerType
{
    Input,
    Condition
};

typedef struct _State
{
    int state_id; // This is corresponding to the state location in the enum
    void* state_function; // Function that continuously runs during the state
} State;

typedef struct _STransition
{
    int state;
    int event_trigger;
    int32_t (*transition_handler)(void);
} STransition;

void
transition(int current_state, node_t* queue, STransition* transitions,
           uint32_t n_transitions);

void
print_state_quote(int state);

#endif // !FSM_H
