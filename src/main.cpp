#include "cop.h"
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

    Cop cop;
    cop.active_state = OnStakeOut;
    cop.dutyTime = 0;
    cop.events = NULL;

    while (true) {
        update_robber(&robber, &cop);
        update_cop(&cop, &robber);
        process_events(&robber.active_state, &robber.events,
                       get_transition_table_robber(), n_transitions_robber);
        process_events(&cop.active_state, &cop.events,
                       get_transition_table_cop(), n_transitions_cop);

        // sleep:
#ifdef _WIN32
        // Sleep(1000);
#else
        /* sleep(1); */
#endif
    }

    return 0;
}
