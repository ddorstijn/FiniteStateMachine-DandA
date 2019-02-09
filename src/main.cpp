#include "robber.h"

int
main(int argc, char const* argv[])
{
    State state = RobbingBank;

    while (true) {
        transition(&state);
    }

    return 0;
}