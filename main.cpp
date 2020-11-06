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
uint32_t minMaxClique(uint32_t nodeCount, uint32_t edgeCount);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    // int t;
    // stringstream stream{reader->readLine()};
    // stream >> t;

    // for (int i = 0; i < t; i++) {
    //     stream = stringstream{reader->readLine()};
    //     uint32_t n, m;
    //     stream >> n >> m;
    //     cout << minMaxClique(n, m) << endl;
    // }

    cout << turansUpperBound(19, 13) << endl;

    return 0;
}

// Turan's theorem: graph with nodeCount vertices, free of K_cliqueSize_+_1
// Maximum number of edges
uint32_t turansUpperBound(uint32_t nodeCount, uint32_t cliqueSize) {
    uint32_t r = nodeCount % cliqueSize;
    return (float(cliqueSize) - 1) * nodeCount * nodeCount / (2 * cliqueSize) -
           (float(r) * (cliqueSize - r) / (2 * cliqueSize));
}

uint32_t minMaxClique(uint32_t nodeCount, uint32_t edgeCount) {
    uint32_t maxSize = nodeCount;
    uint32_t minSize = 2;
    uint32_t minMax = (minSize + maxSize) / 2;

    while (maxSize - minSize > 1) {
        uint32_t maxEdge = turansUpperBound(nodeCount, minMax);
        uint32_t maxEdgeLow = turansUpperBound(nodeCount, minMax - 1);
        if (edgeCount > maxEdgeLow && edgeCount <= maxEdge) return minMax;
        if (maxEdge > edgeCount)
            maxSize = minMax;
        else
            minSize = minMax;
        minMax = (minSize + maxSize) / 2;
    }

    if (turansUpperBound(nodeCount, minSize) >= edgeCount) return minSize;
    return maxSize;
}