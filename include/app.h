#ifndef APP_H
#define APP_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class App {
public:
    std::vector<std::string> state;
    static void run();
};

#endif // APP_H