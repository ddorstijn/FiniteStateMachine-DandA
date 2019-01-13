#include "fsm.h"

int
main(int argc, char const* argv[])
{
    State state = RobbingBank;

    while (true) {
        // First quote what the thif is doing currently
        print_state_quote(state);
        // Flush the input buffer
        fseek(stdin, 0, SEEK_END);
        // Indicate the user can write
        printf("> ");
        // Get user input
        std::string input;
        getline(std::cin, input);
        if (input.empty()) {
            return 0;
        }

        // Transition into next state based on user input
        transition(&state, input);
    }

    return 0;
}