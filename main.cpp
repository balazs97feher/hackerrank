#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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

int64_t minimumBribes(const vector<uint32_t>& q) {
    int64_t minBribes = 0;

    vector<uint32_t> lowestOnward(q.size(), 0);
    uint32_t currentLowest = q[q.size() - 1];
    for (int i = q.size() - 1; i >= 0; i--) {
        if (q[i] < currentLowest) currentLowest = q[i];
        lowestOnward[i] = currentLowest;
    }

    for (size_t i = 0; i < q.size(); i++) {
        int64_t minBribesFori = 0;
        for (size_t j = i + 1; j < q.size(); j++) {
            if (q[j] < q[i]) minBribesFori++;
            if (lowestOnward[j] > q[i]) break;
        }

        if (minBribesFori > 2) return -1;
        else minBribes += minBribesFori;
    }

    return minBribes;
}

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    uint32_t t, n;

    stringstream stream{ reader->readLine() };
    stream >> t;

    while (t--) {
        stream = stringstream{ reader->readLine() };
        stream >> n;
        stream = stringstream{ reader->readLine() };

        vector<uint32_t> q(n, 0);
        for (auto& p : q) stream >> p;

        const auto minBribes = minimumBribes(q);
        if (minBribes == -1) cout << "Too chaotic" << endl;
        else cout << minBribes << endl;
    }

    return 0;
}
