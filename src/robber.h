#ifndef ROBBER_H
#define ROBBER_H

#include <iostream>
#include <string.h>

enum State
{
    RobbingBank,
    HavingGoodTime,
    Fleeing,
    LayingLow,
    Gambling,
    Imprisoned
};

void
transition(State* current_state, std::string trigger);

void
print_state_quote(State state);

#endif // ROBBER_H