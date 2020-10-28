#include <fstream>
#include <iostream>
#include <list>
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

struct WordStart {
    enum Direction { kRight,
                     kDown } direction;
    int y, x, length;

    WordStart(int y, int x, int length, Direction dir) : y(y), x(x), length(length), direction(dir) {}
};

vector<WordStart> findStartFields(const vector<vector<char>> &puzzle);
vector<string> parseWords(string wordList);

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

    auto words = parseWords(reader->readLine());

    // auto startFields = findStartFields(puzzle);

    // for (auto &start : startFields) {
    //     cout << start.y << ' ' << start.x << ' ' << start.length << endl;
    // }

    return 0;
}

vector<WordStart> findStartFields(const vector<vector<char>> &puzzle) {
    vector<WordStart> startFields;

    for (int i = 0; i < kPuzzleSize; i++) {
        int j = 0;
        while (j < kPuzzleSize - 1) {
            if (puzzle[i][j] == '-' && puzzle[i][j + 1] == '-') {
                int length = 0;
                WordStart start(i, j, 0, WordStart::Direction::kRight);
                while (j < kPuzzleSize && puzzle[i][j] == '-') {
                    j++;
                    length++;
                }
                start.length = length;
                startFields.push_back(start);
            }
            j++;
        }
    }

    for (int j = 0; j < kPuzzleSize; j++) {
        int i = 0;
        while (i < kPuzzleSize - 1) {
            if (puzzle[i][j] == '-' && puzzle[i + 1][j] == '-') {
                int length = 0;
                WordStart start(i, j, 0, WordStart::Direction::kDown);
                while (i < kPuzzleSize && puzzle[i][j] == '-') {
                    i++;
                    length++;
                }
                start.length = length;
                startFields.push_back(start);
            }
            i++;
        }
    }

    return startFields;
}

vector<string> parseWords(string wordList) {
    vector<string> words;
    size_t pos = 0;
    string token;

    while ((pos = wordList.find(';')) != string::npos) {
        token = wordList.substr(0, pos);
        words.push_back(token);
        wordList.erase(0, pos + 1);
    }
    words.push_back(wordList);

    return words;
}