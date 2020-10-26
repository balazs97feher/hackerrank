#include <algorithm>
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

static vector<int> coins;

long getWays(int amount, int nextCoin);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{reader->readLine()};
    int amount, m;
    stream >> amount >> m;

    coins.resize(m);
    stream = stringstream{reader->readLine()};
    for (int i = 0; i < m; i++) stream >> coins[i];
    sort(coins.begin(), coins.end(), std::greater<int>());

    auto result = getWays(amount, 0);
    cout << result;

    return 0;
}

long getWays(int amount, int nextCoin) {
    if (amount == 0) return 1;

    long ways = 0;

    if (nextCoin == coins.size() - 1) {
        if (amount % coins[nextCoin] == 0) return 1;
        return 0;
    }

    ways += getWays(amount, nextCoin + 1);
    while (amount >= coins[nextCoin]) {
        amount = amount - coins[nextCoin];
        ways += getWays(amount, nextCoin + 1);
    }

    return ways;
}