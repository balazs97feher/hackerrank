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

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };
    int n, k, rq, cq;
    stream >> n >> k;

    stream = stringstream{ reader->readLine() };
    stream >> rq >> cq;

    vector<pair<int, int>> obstacles;
    obstacles.reserve(k);
    for (int i = 0; i < k; i++) {
        stream = stringstream{ reader->readLine() };
        int row, col;
        stream >> row >> col;
        obstacles.emplace_back(pair<int, int>{ row, col });
    }

    for (auto& o : obstacles) {
        auto [row, col] = o;
        cout << row << ' ' << col << endl;
    }


    return 0;
}
