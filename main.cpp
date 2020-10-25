#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace read {
class Reader {
   public:
    Reader() {}
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
    ConsoleReader() : Reader() {}
    string readLine() override {
        string line;
        getline(cin, line);
        return line;
    }
};
}  // namespace read

using namespace read;

static int boardSize;
vector<vector<int>> knightLOnAChessboard();
int knightL(int a, int b);
int getSquareId(int i, int j);
vector<int> getNeighbors(int i, int j, int a, int b);

main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream ss{reader->readLine()};
    ss >> boardSize;

    vector<vector<int>> result = knightLOnAChessboard();

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j != result[i].size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<vector<int>> knightLOnAChessboard() {
    vector<vector<int>> result(boardSize - 1);
    for (int i = 0; i < boardSize - 1; i++) result[i].resize(boardSize - 1);

    for (int i = 0; i < boardSize - 1; i++) {
        for (int j = i; j < boardSize - 1; j++) {
            result[i][j] = knightL(i + 1, j + 1);
            result[j][i] = result[i][j];
        }
    }

    return result;
}

int knightL(int a, int b) {
    if (a == b) {
        return ((boardSize - 1) % a == 0) ? (boardSize - 1) / a : -1;
    }

    vector<vector<int>> board(boardSize);
    for (int i = 0; i < boardSize; i++) {
        board[i].resize(boardSize);
        for (int j = 0; j < boardSize; j++) board[i][j] = -1;
    }

    return 0;
}

int getSquareId(int i, int j) {
    if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) return i * boardSize + j;
    return -1;
}

vector<int> getNeighbors(int i, int j, int a, int b) {
}