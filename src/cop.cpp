#include "cop.h"

#include <stdio.h>
#include <stdlib.h>

const uint8_t max_duty_time = 12;

const static char* state_qoutes[] = {
    "Relaxing on the sofa, watching Crime Scene Investigation",
    "I'm going around looking to bring justice to the unjust!",
    "Currently chasing a robber! I repeat: Currently in pursuit!"
};

///                 ///
/// State functions ///
///                 ///

void
off_duty(Cop* cop)
{
    cop->dutyTime--;

    if (cop->dutyTime <= 0) {
        enqueue(&cop->events, StartDuty);
    }
}

void
on_stake_out(Cop* cop)
{
    cop->dutyTime++;

    if (cop->dutyTime >= max_duty_time) {
        enqueue(&cop->events, FinishDuty);
    }
}

void
chasing(Cop* cop)
{
    cop->dutyTime++;

    if (cop->dutyTime >= max_duty_time) {
        enqueue(&cop->events, FinishDuty);
    }
}

static void (*state_functions[])(Cop*) = { &off_duty, &on_stake_out, &chasing };

///                 ///
/// Event functions ///
///                 ///

int
start_duty()
{
    printf("Time to be the bringer of justice again. \n");
    print_state_quote(OnStakeOut, state_qoutes);
    return OnStakeOut;
}

int
finish_duty()
{
    printf("It's been a long day. It's been a good day, Time to go home. \n");
    print_state_quote(OffDuty, state_qoutes);
    return OffDuty;
}

int
spot_robber()
{
    printf("Oh dear! That's a robber. I've got to catch him! \n");
    print_state_quote(Chasing, state_qoutes);
    return Chasing;
}

const STransition transitions[] = { { OffDuty, StartDuty, &start_duty },
                                    { OnStakeOut, FinishDuty, &finish_duty },
                                    { OnStakeOut, SpotRobber, &spot_robber },
                                    { Chasing, FinishDuty, &finish_duty } };

//
void
update_cop(Cop* cop)
{
    (*state_functions[cop->active_state])(cop);
}

const STransition*
get_transition_table_cop()
{
    return transitions;
}
