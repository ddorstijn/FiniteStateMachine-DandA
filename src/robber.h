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
    State state;
    uint32_t money;
    uint8_t comfort_level;
    uint8_t boredness;
    node_t* event_queue;
} Robber;

enum Events
{
    GetRich,
    SpotCop,
    GetTired,
    GetBored,
    FeelSafe,
    GetCaught,
    GetBroke
};

#endif // ROBBER_H