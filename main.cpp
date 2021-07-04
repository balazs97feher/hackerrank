#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

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

    int n, k;
    stringstream stream{ reader->readLine() };
    stream >> n >> k;

    stream = stringstream{ reader->readLine() };

    priority_queue<uint64_t, vector<uint64_t>, greater<uint64_t>> candies;

    while (n--) {
        int c;
        stream >> c;
        candies.push(c);
    }

    int iter = 0;
    while (candies.top() < k && candies.size() >= 2) {
        int c1 = candies.top();
        candies.pop();
        int c2 = candies.top();
        candies.pop();

        candies.push(c1 + c2 + c2);
        iter++;
    }

    cout << ((candies.top() >= k) ? iter : -1);

    return 0;
}
