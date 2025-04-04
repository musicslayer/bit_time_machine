#include "app.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const int MAX_FILE_SIZE = 70000; // Bytes
const int MAX_NUMBER_OF_STATES = 100;

std::string inputfile;
std::string outputfile;
std::vector<std::string> state;

int s = 0;
int current;

int main() {
    App app = App();
    app.run();
    return 0;
}

/*
int mainX() {
    while(true) {
        clearScreen();

        current = 0;

        while(true) {
            //Choosing input file
            std::cout << "Choose a file to track." << std::flush;

            std::getline(std::cin, inputfile);

            clearScreen();

            if(std::filesystem::exists(inputfile)) {
                break;
            }
        }

        // Choosing output file
        std::cout << "Choose the output file." << std::flush;

        std::getline(std::cin, outputfile);

        // Main loop
        while(true) {
            //Display info
            updateDisplay();

            char i;

            while(true) {
                std::string userInput;
                std::getline(std::cin, userInput);

                if(!userInput.empty() && userInput.length() == 1) {
                    i = userInput[0];
                    std::cout << userInput << std::flush;
                    break;
                }
            }

            if(i == 's') {
                if(s < MAX_NUMBER_OF_STATES) {
                    //Save current input file state to first unused spot
                    textRead(inputfile);

                    std::cout << "Saved state." << std::flush;
                    current = s;
                    s++;
                }
            }
            else if(i == 'r') {
                //Restore a saved state to the output file

                while(true) {
                    updateDisplay();
                    std::cout << "\nSelect a state to restore." << std::flush;

                    // Select state
                    std::string userInput;
                    std::getline(std::cin, userInput);
                    if(userInput.length() == 1) {
                        try {
                            int c1 = std::stoi(userInput);

                            if(c1 < s && c1 > 0) {
                                std::ofstream file(outputfile, std::ios::binary);
                                file << state[c1];
                                file.close();
                                std::cout << "Restored state." << std::flush;
                                break;
                            }
                            else {
                                std::cout << "Invalid state." << std::flush;
                            }
                        }
                        catch(const std::invalid_argument& e) {
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
            }
            else if(i == 'q') {
                return 0;
            }
            else {
                std::cout << "Invalid command." << std::endl;
            }
        }
    }
}
*/


void textRead(std::string filename) {
    // Write contents of file "filename" to the current state
    std::ifstream file(filename, std::ios::binary);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    state.push_back(buffer.str());
    file.close();
}

