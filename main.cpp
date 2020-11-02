#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace reader {
class Reader {
   public:
    Reader() = default;
    virtual string readLine() = 0;
};

class FileReader : public Reader {
    std::ifstream inputFile;

   public:
    FileReader(const string fileName) : Reader() {
        inputFile = ifstream(fileName);
    }
    string readLine() override {
        string line;
        getline(inputFile, line);
        return line;
    }
};

class ConsoleReader : public Reader {
   public:
    ConsoleReader() = default;
    string readLine() override {
        string line;
        getline(cin, line);
        return line;
    }
};
}  // namespace reader

using namespace reader;

uint32_t turansUpperBound(uint32_t nodeCount, uint32_t cliqueSize);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    return 0;
}

// Turan's theorem: graph with nodeCount vertices, free of K_cliqueSize_+_1
// Maximum number of edges
uint32_t turansUpperBound(uint32_t nodeCount, uint32_t cliqueSize) {
    uint32_t r = nodeCount % cliqueSize;
    return (cliqueSize - 1) / (2 * cliqueSize) * nodeCount * nodeCount -
           (r * (cliqueSize - r) / (2 * cliqueSize));
}