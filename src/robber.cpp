#include "robber.h"

#include <stdio.h>
#include <stdlib.h>

const static char* state_qoutes[] = {
    "I'm robbing banks and getting loads of money! Pew pew!",
    "I'm having a good time spending my money.",
    "I'm currently on the run.",
    "I'm taking it easy and laying low for now.",
    "I feel like the luckiest man on earth! Let's go casino. ",
    "I got caught and have to spand time in prison :("
};

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
        return;
    }

    if (rand() % 20 == 0) {
        robber->distance_to_cop = 0;
        enqueue(&robber->events, SpotCop);
        return;
    }
}

void
having_good_time(Robber* robber)
{
    robber->wealth -= 2;
    robber->boredness++;

    if (robber->wealth < 0) {
        enqueue(&robber->events, GetBroke);
        return;
    }

    if (robber->boredness > 15) {
        enqueue(&robber->events, GetBored);
        robber->boredness = 0;
        return;
    }

    if (rand() % 20 == 0) {
        robber->distance_to_cop = 0;
        enqueue(&robber->events, SpotCop);
        return;
    }
}

void
fleeing(Robber* robber)
{
    robber->wealth--;

    if (rand() % 10 == 0) {
        enqueue(&robber->events, GetCaught);
        return;
    }

    if (rand() % 10 == 0) {
        enqueue(&robber->events, GetTired);
        return;
    }

    if (rand() % 10 == 0) {
        robber->distance_to_cop = 10;
        enqueue(&robber->events, FeelSafe);
        return;
    }
}

void
laying_low(Robber* robber)
{
    robber->strength++;

    if (robber->strength > 30) {
        enqueue(&robber->events, FeelSafe);
        return;
    }
}

void
gambling(Robber* robber)
{
    robber->wealth -= 5;

    if (robber->wealth < 0) {
        enqueue(&robber->events, GetBroke);
        return;
    }

    if (rand() % 10 == 0) {
        robber->distance_to_cop = 10;
        enqueue(&robber->events, FeelSafe);
        return;
    }
}

void
imprisoned(Robber* robber)
{
    robber->strength++;

    if (robber->strength > 15) {
        enqueue(&robber->events, EscapePrison);
        return;
    }
}

static void (*state_functions[])(Robber*) = { robbing_bank, having_good_time,
                                              fleeing,      laying_low,
                                              gambling,     imprisoned };

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

const STransition transitions[] = {
    { RobbingBank, GetRich, &get_rich },
    { RobbingBank, SpotCop, &spot_cop },
    { HavingGoodTime, GetTired, &get_tired },
    { HavingGoodTime, GetBroke, &get_broke },
    { HavingGoodTime, SpotCop, &spot_cop },
    { HavingGoodTime, GetBored, &get_bored },
    { Fleeing, FeelSafe, &feel_safe },
    { Fleeing, GetTired, &get_tired },
    { Fleeing, GetCaught, &get_caught },
    { LayingLow, FeelSafe, &feel_safe },
    { Gambling, SpotCop, &spot_cop },
    { Gambling, GetBroke, &get_broke },
    { Imprisoned, EscapePrison, &escape },
};

void
update_robber(Robber* robber)
{
    (*state_functions[robber->active_state])(robber);
}

const STransition*
get_transition_table_robber()
{
    return transitions;
}