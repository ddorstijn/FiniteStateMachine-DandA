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
    }

    return 0;
}