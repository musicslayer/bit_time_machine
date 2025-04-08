#include "app.h"
#include "file_state.h"

void App::run() {
    FileState fileState =
        FileState::fromFile("C:\\GITHUB\\bit_time_machine\\sample\\sample.txt");
    fileState.toFile("C:/GITHUB/bit_time_machine/sample/sample2.txt");
}