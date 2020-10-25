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

vector<vector<int>> knightLOnAChessboard(int n);
int knightL(int n, int a, int b);

main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n;
    stringstream ss{reader->readLine()};
    ss >> n;

    vector<vector<int>> result = knightLOnAChessboard(n);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j != result[i].size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<vector<int>> knightLOnAChessboard(int n) {
    vector<vector<int>> result(n - 1);
    for (int i = 0; i < n - 1; i++) result[i].resize(n - 1);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n - 1; j++) {
            result[i][j] = knightL(n, i + 1, j + 1);
            result[j][i] = result[i][j];
        }
    }

    return result;
}

int knightL(int n, int a, int b) {
    return -1;
}