#include <fstream>
#include <iostream>
#include <list>
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
vector<int> getNeighbors(int squareId, int a, int b);

int main(int argc, char *argv[]) {
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

    vector<int> board(boardSize * boardSize);  // stores the minimum number of steps to reach a square from 0,0
    for (auto &square : board) square = -1;

    list<int> squaresToCheck{0};
    board[0] = 0;  // BFS from 0,0
    do {
        int currentSquare = squaresToCheck.front();
        squaresToCheck.pop_front();

        auto neighbors = getNeighbors(currentSquare, a, b);
        for (auto neighbor : neighbors) {
            if (board[neighbor] == -1) {
                board[neighbor] = board[currentSquare] + 1;
                squaresToCheck.push_back(neighbor);
            }
        }

    } while (false == squaresToCheck.empty());

    return board[boardSize * boardSize - 1];
}

int getSquareId(int i, int j) {
    if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) return i * boardSize + j;
    return -1;
}

vector<int> getNeighbors(int squareId, int a, int b) {
    int i = squareId / boardSize;
    int j = squareId % boardSize;

    const vector<int> stepsi{a, a, -a, -a, b, b, -b, -b};
    const vector<int> stepsj{b, -b, b, -b, a, -a, a, -b};

    vector<int> neighbors;
    neighbors.reserve(8);

    for (int k = 0; k < 8; k++) {
        int neighbor = getSquareId(i + stepsi[k], j + stepsj[k]);
        if (neighbor != -1) neighbors.push_back(neighbor);
    }

    return neighbors;
}