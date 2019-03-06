#ifndef COP_H
#define COP_H

#include "fsm.h"

typedef struct _Cop
{
    int active_state;
    int dutyTime;

    node_t* events; // An event queue for transition events
} Cop;

enum CopState
{
    OffDuty,
    OnStakeOut,
    Chasing
};

enum CopEvents
{
    StartDuty,
    FinishDuty,
    SpotRobber
};

void
update_cop(Cop* cop);

const STransition*
get_transition_table_cop();

const uint16_t n_transitions_cop = 4;

#endif // COP_H
