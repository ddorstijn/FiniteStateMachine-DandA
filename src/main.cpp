#include "robber.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int
main(int argc, char const* argv[])
{
    Robber robber;
    robber.active_state = RobbingBank;
    robber.wealth = 0;
    robber.comfort = 10;
    robber.strength = 10;
    robber.distance_to_cop = 10;
    robber.events = NULL;

    while (true) {
        (*state_functions[robber.active_state])(&robber);
        process_events(&robber.active_state, &robber.events, transitions,
                       n_transitions);

        // sleep:
#ifdef _WIN32
        // Sleep(1000);
#else
        // sleep(1);
#endif
    }

    return 0;
}
