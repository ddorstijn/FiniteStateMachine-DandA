#ifndef ROBBER_H
#define ROBBER_H

#include "fsm.h"

typedef struct _Robber
{
    int active_state;
    int32_t wealth;          // Money levels
    uint8_t comfort;         // Comfort level in percentage
    uint8_t boredness;       // Bored level in percentage
    uint8_t strength;        // Strength level in percentage
    uint8_t distance_to_cop; // 0 if is getting caught

    node_t* events; // An event queue for transition events
} Robber;

enum RobberState
{
    RobbingBank,
    HavingGoodTime,
    Fleeing,
    LayingLow,
    Gambling,
    Imprisoned
};

enum RobberEvents
{
    GetRich,
    SpotCop,
    GetTired,
    GetBored,
    FeelSafe,
    GetCaught,
    GetBroke,
    EscapePrison
};

void
update_robber(Robber* robber);

const STransition*
get_transition_table_robber();

const uint16_t n_transitions_robber = 13;

#endif // ROBBER_H
