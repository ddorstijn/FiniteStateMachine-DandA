#include "fsm.h"

#include <stdio.h>

void
process_events(int* current_state, node_t** event_queue,
               const STransition* transitions, uint32_t n_transitions)
{
    int event = dequeue(event_queue);
    if (event < 0) {
        return;
    }

    // Seek correct state transition handler
    for (uint32_t i = 0; i < n_transitions; i++) {
        if (*current_state == transitions[i].state) {
            if (event == transitions[i].event_trigger) {
                *current_state = (int)(transitions[i].transition_handler)();
                return;
            }
        }
    }
}

void
print_state_quote(int state, const char** state_qoutes)
{
    // Print out current state sentence
    printf("%s\n", state_qoutes[state]);
}
