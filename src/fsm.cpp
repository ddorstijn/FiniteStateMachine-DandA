#include "fsm.h"

const char* state_qoutes[] = {
    "I'm robbing banks and getting loads of money! Pew pew!",
    "I'm having a good time spending my money.",
    "I'm currently on the run.",
    "I'm taking it easy and laying low for now.",
    "I feel like the luckiest man on earth! Let's go casino. ",
    "I got caught and have to spand time in prison :("
};

static enum State
get_rich()
{
    printf("I'm rich enough to have a good time.\n");
    return HavingGoodTime;
}

static enum State
get_tired()
{
    printf("I'm getting tired. Let's take it a bit easier.\n");
    return LayingLow;
}

static enum State
get_caught()
{
    printf("Oh no! The cops are closing in! Nooo, they got me!\n");
    return Imprisoned;
}

static enum State
get_bored()
{
    printf("I'm so rich. I'm getting bored. Let's do something fun.\n");
    return Gambling;
}

static enum State
get_broke()
{
    printf("I had an unlucky day. I lost all me money. I'm screwed.\n");
    return LayingLow;
}

static enum State
feel_safe()
{
    printf(
        "I haven't seen any cops in a while. It seems safe to go outside.\n");
    return RobbingBank;
}

static enum State
escape()
{
    printf("I've thaught of a plan to get out of this stinky place.\n");
    return LayingLow;
}

static enum State
spot_cop()
{
    printf("I see a cop, so I have to start running!\n");
    return Fleeing;
}

typedef struct _STransition
{
    enum State state;
    std::string trigger;
    enum State (*transition_handler)(void);
} STransition;

STransition transitions[] = {
    { RobbingBank, "Get rich", &get_rich },
    { RobbingBank, "Spot cop", &spot_cop },
    { HavingGoodTime, "Get tired", &get_tired },
    { HavingGoodTime, "Spot cop", &spot_cop },
    { HavingGoodTime, "Get bored", &get_bored },
    { Fleeing, "Feel safe", &feel_safe },
    { Fleeing, "Get tired", &get_tired },
    { Fleeing, "Get caught", &get_caught },
    { LayingLow, "Feel safe", &feel_safe },
    { Gambling, "Spot cop", &spot_cop },
    { Gambling, "Get broke", &get_broke },
    { Imprisoned, "Get caught", &get_caught },
};

const short n_transitions = 12;

void
transition(State* current_state, std::string trigger)
{
    // Seek correct state transition handler
    for (short i = 0; i < n_transitions; i++) {
        if (*current_state == transitions[i].state) {
            if (trigger == transitions[i].trigger) {
                *current_state = (transitions[i].transition_handler)();
                return;
            }
        }
    }
    // If no match was found
    std::cout << "No match was found for: " << trigger << std::endl;
    printf("Possible inputs: \n");
    for (int i = 0; i < n_transitions; i++) {
        if (*current_state == transitions[i].state) {
            std::cout << "  - " << transitions[i].trigger << std::endl;
        }
    }
}

void
print_state_quote(State state)
{
    // Print out current state sentence
    printf("%s\n", state_qoutes[state]);
}