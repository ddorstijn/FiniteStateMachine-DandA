#ifndef ROBBER_H
#define ROBBER_H

#include "fsm.h"

enum State
{
    RobbingBank,
    HavingGoodTime,
    Fleeing,
    LayingLow,
    Gambling,
    Imprisoned
};

typedef struct _Robber
{
    int active_state;
    uint32_t wealth;
    uint8_t comfort;   // Comfort level in percentage
    uint8_t boredness; // Bored level in percentage
    uint8_t strength;  // Strength level in percentage
    uint8_t distance_to_cop;

    node_t* events;
} Robber;

enum Events
{
    GetRich,
    SpotCop,
    GetTired,
    GetBored,
    FeelSafe,
    GetCaught,
    GetBroke,
    Escape
};

///                 ///
/// State functions ///
///                 ///

void
robbing_bank(Robber* robber);

void
having_good_time(Robber* robber);

void
fleeing(Robber* robber);

void
laying_low(Robber* robber);

void
gambling(Robber* robber);

void
imprisoned(Robber* robber);

static void (*state_functions[6])(Robber*) = { robbing_bank, having_good_time,
                                               fleeing,      laying_low,
                                               gambling,     imprisoned };

const static char* state_qoutes[] = {
    "I'm robbing banks and getting loads of money! Pew pew!",
    "I'm having a good time spending my money.",
    "I'm currently on the run.",
    "I'm taking it easy and laying low for now.",
    "I feel like the luckiest man on earth! Let's go casino. ",
    "I got caught and have to spand time in prison :("
};

///                 ///
/// Event functions ///
///                 ///

int
get_rich();

int
get_tired();

int
get_caught();

int
get_bored();

int
get_broke();

int
feel_safe();

int
escape();

int
spot_cop();

const static STransition transitions[] = {
    { RobbingBank, GetRich, &get_rich },
    { RobbingBank, SpotCop, &spot_cop },
    { HavingGoodTime, GetTired, &get_tired },
    { HavingGoodTime, SpotCop, &spot_cop },
    { HavingGoodTime, GetBored, &get_bored },
    { Fleeing, FeelSafe, &feel_safe },
    { Fleeing, GetTired, &get_tired },
    { Fleeing, GetCaught, &get_caught },
    { LayingLow, FeelSafe, &feel_safe },
    { Gambling, SpotCop, &spot_cop },
    { Gambling, GetBroke, &get_broke },
    { Imprisoned, Escape, &escape },
};

const uint16_t n_transitions = 12;

#endif // ROBBER_H
