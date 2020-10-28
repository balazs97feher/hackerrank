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

static const int kPuzzleSize = 10;

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    vector<vector<char>> puzzle(kPuzzleSize);
    for (int i = 0; i < kPuzzleSize; i++) {
        puzzle[i].resize(kPuzzleSize);

        stringstream stream{reader->readLine()};
        for (int j = 0; j < kPuzzleSize; j++) puzzle[i][j] = stream.get();
    }

    // for (auto row : puzzle) {
    //     for (auto c : row) cout << c;
    //     cout << endl;
    // }

    return 0;
}