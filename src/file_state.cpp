#include "file_state.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

FileState FileState::fromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    // Return an empty object?
    if(!file) {
        throw std::runtime_error("Failed to find file");
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    FileState fileState = FileState();
    fileState.data = std::vector<std::byte>(size);
    if (!file.read(reinterpret_cast<char*>(fileState.data.data()), size)) {
        throw std::runtime_error("Failed to read file");
    }

    return fileState;
}

void FileState::toFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if(!file) {
        throw std::runtime_error("Failed to open file for writing");
    }

    file.write(reinterpret_cast<const char*>(this->data.data()), this->data.size());
    if(!file) {
        throw std::runtime_error("Failed to write data to file");
    }

    file << "test" << std::flush;
    file << this->data.size() << std::flush;
}