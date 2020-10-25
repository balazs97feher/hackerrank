#include <algorithm>
#include <cmath>
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
}  // namespace reader

using namespace reader;

int formingMagicSquare(vector<vector<int>>& s);
void reflect(vector<vector<int>>& s);
void rotate(vector<vector<int>>& s);
int absoluteDifference(vector<vector<int>>& s1, vector<vector<int>>& s2);

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    vector<vector<int>> s(3);
    for (int i = 0; i < 3; i++) {
        s[i].resize(3);
        stringstream ss{reader->readLine()};
        for (int j = 0; j < 3; j++) {
            ss >> s[i][j];
        }
    }

    int result = formingMagicSquare(s);
    cout << result << endl;

    return 0;
}

int formingMagicSquare(vector<vector<int>>& s) {
    vector<vector<int>> threeOrder{{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};

    int minCost = absoluteDifference(s, threeOrder);
    int cost = minCost;
    for (int i = 1; i <= 3; i++) {
        rotate(threeOrder);
        cost = absoluteDifference(s, threeOrder);
        if (cost < minCost) minCost = cost;
    }

    reflect(threeOrder);
    cost = absoluteDifference(s, threeOrder);
    if (cost < minCost) minCost = cost;

    for (int i = 1; i <= 3; i++) {
        rotate(threeOrder);
        cost = absoluteDifference(s, threeOrder);
        if (cost < minCost) minCost = cost;
    }

    return minCost;
}

void reflect(vector<vector<int>>& s) {
    for (int i = 0; i < s.size(); i++)
        for (int j = i + 1; j < s.size(); j++) swap(s[i][j], s[j][i]);
}

void rotate(vector<vector<int>>& s) {
    const int n = s.size();
    vector<vector<int>> rotated(n);
    for (int i = 0; i < n; i++) rotated[i].resize(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) rotated[i][j] = s[n - j - 1][i];

    s = rotated;
}

int absoluteDifference(vector<vector<int>>& s1, vector<vector<int>>& s2) {
    int diff = 0;
    for (int i = 0; i < s1.size(); i++)
        for (int j = 0; j < s1.size(); j++) diff += abs(s1[i][j] - s2[i][j]);

    return diff;
}