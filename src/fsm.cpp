#include "fsm.h"

void
transition(int current_state, node_t* queue, STransition* transitions,
           uint n_transitions)
{
    int event = dequeue(&queue);
    // Seek correct state transition handler
    for (short i = 0; i < n_transitions; i++) {
        if (current_state == transitions[i].state) {
            if (event == transitions[i].event_trigger) {
                current_state = (int)(transitions[i].transition_handler)();
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