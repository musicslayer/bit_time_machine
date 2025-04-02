#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const int MAX_FILE_SIZE = 70000; // Bytes
const int MAX_NUMBER_OF_STATES = 100;

std::string inputfile;
std::string outputfile;
std::string backupfile;
std::string state[MAX_NUMBER_OF_STATES];

int s = 0;
int current;

void clearScreen(void);
void textRead(std::string);
void updateDisplay(void);

int main() {
    while(true) {
        clearScreen();

        current = 0;

        while(true) {
            //Choosing input file
            std::cout << "Choose a file to track." << std::flush;

            std::getline(std::cin, inputfile);

            std::ifstream file(inputfile, std::ios::binary);

            clearScreen();
            if(file) {
                file.close();
                break;
            }
        }

        // Opening backup file or creating new backup file
        backupfile = inputfile + ".backup";
        
        std::ifstream file(backupfile, std::ios::binary);

        // If the backup file exists
        if(file) {
            //fseek(fp, 0, SEEK_SET); 
            for(int c1 = 0; c1 < MAX_NUMBER_OF_STATES; c1++) {
                //fscanf(fp, "%i", &sizeofstate[c1]);  
                //fread(&state[c1][0], 1, 1, fp);  
                for(int c2 = 0; c2 < state[c1].length(); c2++) {
                    //fread(&state[c1][c2], 1, 1, fp);  
                }

                //if(feof(fp) != 0) {
                //    current = s - 1;
                //    break;
                //}

                s++;
            }

            //fclose(fp);
            file.close();
        }

        // If the backup file doesn't exist
        else {
            textRead(inputfile);
            s++;
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
                int c = time(NULL);
                while(time(NULL) - c < .1);

                textRead(inputfile);

                if(s < MAX_NUMBER_OF_STATES && state[s] != state[s-1]) {
                    //std::cout << "Automatically saved state." << std::flush;
                    current = s;
                    s++;

                    //Display info
                    updateDisplay();
                }

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

                    //std::cout << "Saved state." << std::flush;
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
                    char j = '\n';
                    while(j == '\n') {
                        fgets(&j, 10, stdin);
                    }

                    if(j == '0') {
                        std::ofstream file(outputfile, std::ios::binary);
                        //fwrite(state[0], 1, sizeofstate[0], fp);
                        file.close();
                        std::cout << "Restored state." << std::flush;
                        break;
                    }
                    else {
                        int c1 = atoi(&j);
                        if(c1 < s && c1 > 0) {
                            //current = c1;
                            std::ofstream file(outputfile, std::ios::binary);
                            //fwrite(state[c1], 1, sizeofstate[c1], fp);
                            file.close();
                            std::cout << "Restored state." << std::flush;
                            break;
                        }
                        else {
                            std::cout << "Invalid state." << std::flush;
                        }
                    }
                }
            }

            else if(i == 'b') {
                // Backup all used states to backup file
                std::ofstream file(backupfile, std::ios::binary);
                for(int c1 = 0; c1 < s; c1++) {
                    //fprintf(fp, "%i\n", sizeofstate[c1]);  
                    for(int c2 = 0; c2 < state[c1].length(); c2++) {
                        //fwrite(&state[c1][c2], 1, 1, fp);
                    }
                }
                file.close();
            }

            else if(i == 'q') {
                break;
            }

            else if(i == 'z') {
                return 0;
            }

            else {
                std::cout << "Invalid command." << std::endl;
            }
        }
    }
}

void clearScreen(void) {
    std::cout << "\033[2J\033[H";
}

void textRead(std::string filename) {
    // Write contents of file "filename" to the current state
    std::ifstream file(filename, std::ios::binary);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    state[s] = buffer.str();

    file.close();
}

void updateDisplay(void) {
    //Display info
    clearScreen();

    std::cout << std::format("Input file = {}\nOutput file = {}\nBackup file = {}\n0", inputfile, outputfile, backupfile);

    for(int c1 = 1; c1 < s; c1++) {
        std::cout << std::format(" {}", c1);
    }
    for(int c1 = s; c1 < MAX_NUMBER_OF_STATES - 1; c1++) {
        std::cout << " X";
    }

    std::cout << std::format("\nCurrent state = {}", current);

    std::cout << std::flush;

    // Ask user what they want to do
    std::cout << "\nPress s to save state, r to restore state, b to backup states, q to reset, z to quit." << std::endl;
}