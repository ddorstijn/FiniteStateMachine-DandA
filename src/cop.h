#ifndef COP_H
#define COP_H

#include "fsm.h"

#include "robber.h"

typedef struct _Robber Robber;

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
    SpotRobber,
    CatchRobber
};

void
update_cop(Cop* cop, Robber* robber);

const STransition*
get_transition_table_cop();

const uint16_t n_transitions_cop = 5;

#endif // COP_H
