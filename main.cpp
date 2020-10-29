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
static vector<string> words;
static vector<bool> used;

struct WordStart {
    enum Direction { kRight,
                     kDown } direction;
    int y, x, length;

    WordStart(int y, int x, int length, Direction dir) : y(y), x(x), length(length), direction(dir) {}
};

static vector<WordStart> startFields;

vector<WordStart> findStartFields(const vector<vector<char>> &puzzle);
vector<string> parseWords(string wordList);
vector<vector<char>> solvePuzzle(const vector<vector<char>> &puzzle, int nextStart);
bool writeWord(vector<vector<char>> &puzzle, const string &word, const WordStart &start);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    vector<vector<char>> puzzle;
    puzzle.resize(kPuzzleSize);
    for (int i = 0; i < kPuzzleSize; i++) {
        puzzle[i].resize(kPuzzleSize);

        stringstream stream{reader->readLine()};
        for (int j = 0; j < kPuzzleSize; j++) puzzle[i][j] = stream.get();
    }

    words = parseWords(reader->readLine());

    startFields = findStartFields(puzzle);
    used.resize(words.size());
    auto result = solvePuzzle(puzzle, 0);

    for (auto &row : result) {
        for (auto field : row) cout << field;
        cout << endl;
    }

    return 0;
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

vector<vector<char>> solvePuzzle(const vector<vector<char>> &puzzle, int nextStart) {
    if (nextStart == startFields.size()) return puzzle;
    // cout << "next> " << nextStart << endl;

    for (int i = 0; i < used.size(); i++) {
        if (used[i] == false && startFields[nextStart].length == words[i].size()) {
            vector<vector<char>> filledPuzzle(puzzle);
            if (writeWord(filledPuzzle, words[i], startFields[nextStart]) == true) {
                used[i] = true;

                //debug
                // for (auto &row : filledPuzzle) {
                //     for (auto field : row) cout << field;
                //     cout << endl;
                // }

                auto solved = solvePuzzle(filledPuzzle, ++nextStart);
                if (solved.empty() == false)
                    return solved;
                else {
                    nextStart--;
                    used[i] = false;
                }
            }
        }
    }

    vector<vector<char>> empty;
    return empty;
}

bool writeWord(vector<vector<char>> &puzzle, const string &word, const WordStart &start) {
    int i = start.y;
    int j = start.x;

    if (start.direction == WordStart::Direction::kRight) {
        while (j < start.x + word.size()) {
            if (puzzle[i][j] != '-' && puzzle[i][j] != word[j - start.x]) break;
            j++;
        }
        if (j != start.x + word.size()) return false;

        j = start.x;
        while (j < start.x + word.size()) {
            puzzle[i][j] = word[j - start.x];
            j++;
        }
        return true;
    } else {
        while (i < start.y + word.size()) {
            if (puzzle[i][j] != '-' && puzzle[i][j] != word[i - start.y]) break;
            i++;
        }
        if (i != start.y + word.size()) return false;
        i = start.y;
        while (i < start.y + word.size()) {
            puzzle[i][j] = word[i - start.y];
            i++;
        }
        return true;
    }
}