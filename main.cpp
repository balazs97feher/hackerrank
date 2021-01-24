#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Reader {
public:
    Reader() = default;
    virtual string readLine() = 0;
};

class FileReader : public Reader {
    ifstream inputFile;

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

struct Field {
    int row, col;
    Field(const int r = -1, const int c = -1) : row(r), col(c) {}
};

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };
    int n, k;
    stream >> n >> k;

    Field queen;
    stream = stringstream{ reader->readLine() };
    stream >> queen.row >> queen.col;
    const int sum = queen.row + queen.col;
    const int diff = queen.row - queen.col;

    Field closestNorth{ n + 1, queen.col }, closestEast{ queen.row, n + 1 },
        closestSouth{ 0, queen.col }, closestWest{ queen.row, 0 };
    Field closestNorthEast, closestSouthEast, closestSouthWest, closestNorthWest;

    if (sum < n) {
        closestNorthWest = Field{ sum, 0 };
        closestSouthEast = Field{ 0, sum };
    }
    else {
        closestNorthWest = Field{ n + 1, sum - n - 1 };
        closestSouthEast = Field{ sum - n - 1, n + 1 };
    }

    if (diff > 0) {
        closestSouthWest = Field{ 0 + diff, 0 };
        closestNorthEast = Field{ n + 1, n + 1 - diff };
    }
    else {
        closestSouthWest = Field{ 0, 0 - diff };
        closestNorthEast = Field{ n + 1 + diff, n + 1 };
    }

    for (int i = 0; i < k; i++) {
        stream = stringstream{ reader->readLine() };
        int row, col;
        stream >> row >> col;

        if (row == queen.row) {
            if (col < queen.col && col > closestWest.col) closestWest = Field{ row, col };
            else if (col > queen.col && col < closestEast.col) closestEast = Field{ row, col };
        }
        else if (col == queen.col) {
            if (row < queen.row && row > closestSouth.row) closestSouth = Field{ row, col };
            else if (row > queen.row && row < closestNorth.row) closestNorth = Field{ row, col };
        }
        else if ((row + col) == sum) {
            if (row > queen.row && row < closestNorthWest.row)  closestNorthWest = Field{ row, col };
            else if (row < queen.row && row > closestSouthEast.row) closestSouthEast = Field{ row, col };
        }
        else if ((row - col) == diff) {
            if (row > queen.row && row < closestNorthEast.row) closestNorthEast = Field{ row, col };
            else if (row < queen.row && row > closestSouthWest.row) closestSouthWest = Field{ row, col };
        }
    }

    int attackable = 0;
    attackable += queen.col - closestWest.col - 1;
    attackable += closestEast.col - queen.col - 1;
    attackable += queen.row - closestSouth.row - 1;
    attackable += closestNorth.row - queen.row - 1;
    attackable += closestNorthWest.row - queen.row - 1;
    attackable += queen.row - closestSouthEast.row - 1;
    attackable += closestNorthEast.row - queen.row - 1;
    attackable += queen.row - closestSouthWest.row - 1;

    cout << attackable;

    return 0;
}
