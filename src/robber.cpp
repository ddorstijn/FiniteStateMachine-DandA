#include "robber.h"

const char* state_qoutes[] = {
    "I'm robbing banks and getting loads of money! Pew pew!",
    "I'm having a good time spending my money.",
    "I'm currently on the run.",
    "I'm taking it easy and laying low for now.",
    "I feel like the luckiest man on earth! Let's go casino. ",
    "I got caught and have to spand time in prison :("
};

static int
get_rich()
{
    printf("I'm rich enough to have a good time.\n");
    return HavingGoodTime;
}

static int
get_tired()
{
    printf("I'm getting tired. Let's take it a bit easier.\n");
    return LayingLow;
}

static int
get_caught()
{
    printf("Oh no! The cops are closing in! Nooo, they got me!\n");
    return Imprisoned;
}

static int
get_bored()
{
    printf("I'm so rich. I'm getting bored. Let's do something fun.\n");
    return Gambling;
}

static int
get_broke()
{
    printf("I had an unlucky day. I lost all me money. I'm screwed.\n");
    return LayingLow;
}

static int
feel_safe()
{
    printf(
        "I haven't seen any cops in a while. It seems safe to go outside.\n");
    return RobbingBank;
}

static int
escape()
{
    printf("I've thaught of a plan to get out of this stinky place.\n");
    return LayingLow;
}

static int
spot_cop()
{
    printf("I see a cop, so I have to start running!\n");
    return Fleeing;
}

const STransition transitions[] = {
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
    { Imprisoned, GetCaught, &get_caught },
};

const uint16_t n_transitions = 12;
