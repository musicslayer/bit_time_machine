#include <cstddef>
#include <string>
#include <vector>

// Represents a single state of the file.
class FileState {
public:
    std::vector<std::byte> data;

    static FileState fromFile(const std::string& filename);
    void toFile(const std::string& filename);
};