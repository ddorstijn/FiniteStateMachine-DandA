#include "robber.h"

#include <stdio.h>
#include <stdlib.h>

///                 ///
/// State functions ///
///                 ///

void
robbing_bank(Robber* robber)
{
    robber->wealth += 3;
    robber->strength--;

    if (robber->wealth > 20) {
        enqueue(&robber->events, GetRich);
    }

    if (rand() % 20 == 0) {
        robber->distance_to_cop = 0;
        enqueue(&robber->events, SpotCop);
    }
}

void
having_good_time(Robber* robber)
{
    robber->wealth--;
    if (rand() % 20 == 0) {
        robber->distance_to_cop = 0;
        enqueue(&robber->events, SpotCop);
    }
}

void
fleeing(Robber* robber)
{
    robber->wealth--;
    if (rand() % 10 == 0) {
        enqueue(&robber->events, GetCaught);
    }
}

void
laying_low(Robber* robber)
{
    robber->strength++;
    if (robber->strength > 30) {
        enqueue(&robber->events, FeelSafe);
    }
}

void
gambling(Robber* robber)
{
    robber->wealth--;
    if (robber->wealth > 30) {
        enqueue(&robber->events, GetBroke);
    }
}

void
imprisoned(Robber* robber)
{
    robber->strength++;
    if (robber->strength > 15) {
        enqueue(&robber->events, Escape);
    }
}

///                 ///
/// Event functions ///
///                 ///

int
get_rich()
{
    printf("I'm rich enough to have a good time.\n");
    print_state_quote(HavingGoodTime, state_qoutes);
    return HavingGoodTime;
}

int
get_tired()
{
    printf("I'm getting tired. Let's take it a bit easier.\n");
    print_state_quote(LayingLow, state_qoutes);
    return LayingLow;
}

int
get_caught()
{
    printf("Oh no! The cops are closing in! Nooo, they got me!\n");
    print_state_quote(Imprisoned, state_qoutes);
    return Imprisoned;
}

int
get_bored()
{
    printf("I'm so rich. I'm getting bored. Let's do something fun.\n");
    print_state_quote(Gambling, state_qoutes);
    return Gambling;
}

int
get_broke()
{
    printf("I had an unlucky day. I lost all me money. I'm screwed.\n");
    print_state_quote(LayingLow, state_qoutes);
    return LayingLow;
}

int
feel_safe()
{
    printf(
        "I haven't seen any cops in a while. It seems safe to go outside.\n");
    print_state_quote(RobbingBank, state_qoutes);
    return RobbingBank;
}

int
escape()
{
    printf("I've thaught of a plan to get out of this stinky place.\n");
    print_state_quote(LayingLow, state_qoutes);
    return LayingLow;
}

int
spot_cop()
{
    printf("I see a cop, so I have to start running!\n");
    print_state_quote(Fleeing, state_qoutes);
    return Fleeing;
}
