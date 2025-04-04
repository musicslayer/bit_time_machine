#include <format>
#include <iostream>

class State {
public:
    void updateDisplay() {
        /*
        //Display info
        clearScreen();

        std::cout << std::format("Input file = {}\nOutput file = {}\n0",
        inputfile, outputfile);

        for(int c1 = 1; c1 < s; c1++) {
            std::cout << std::format(" {}", c1);
        }
        for(int c1 = s; c1 < MAX_NUMBER_OF_STATES - 1; c1++) {
            std::cout << " X";
        }

        std::cout << std::format("\nCurrent state = {}", current);

        std::cout << std::flush;

        // Ask user what they want to do
        std::cout << "\nPress s to save state, r to restore state, b to backup
        states, q to quit." << std::endl;
        */
    }

    void clearScreen() { std::cout << "\033[2J\033[H"; }
};