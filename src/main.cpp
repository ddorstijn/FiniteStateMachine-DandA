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
    robber.state = RobbingBank;

    while (true) {
        // sleep:
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif

        if (robber.state != FeelSafe && robber.state != Imprisoned &&
            rand() % 5 == 0) {
            enqueue(&robber.event_queue, SpotCop);
        }

        if (robber.state == RobbingBank) {
            enqueue(&robber.event_queue, GetRich);
            robber.money = 100000;
            robber.boredness = 0;
        }
    }

    return 0;
}