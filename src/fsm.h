#ifndef FSM_H
#define FSM_H

#include <stdint.h>

#include "queue.h"

enum TriggerType
{
    Input,
    Condition
};

typedef struct _STransition
{
    int state;
    int event_trigger;
    int32_t (*transition_handler)(void);
} STransition;

void
process_events(int* current_state, node_t** event_queue,
               const STransition* transitions, uint32_t n_transitions);

void
print_state_quote(int state, const char** state_qoutes);

#endif // !FSM_H
