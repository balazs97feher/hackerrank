#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

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

int findParent(int* parents, const int elem) {
    auto iter = elem;
    while (parents[iter] > 0) iter = parents[iter];

    // collapse find
    if (iter != elem) return parents[elem] = iter;
    return elem;
}

void takeUnion(int* parents, const int ps, const int pe) {
    if (parents[ps] < parents[pe]) {
        parents[ps] += parents[pe];
        parents[pe] = ps;
    }
    else {
        parents[pe] += parents[ps];
        parents[ps] = pe;
    }
}

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };

    uint16_t n;
    stream >> n;

    int parents[30001];
    for (auto& p : parents) p = -1;

    while (n-- > 0) {
        uint16_t s, e;
        stream = stringstream{ reader->readLine() };
        stream >> s >> e;

        const auto ps = findParent(parents, s);
        const auto pe = findParent(parents, e);
        if (ps != pe) {
            takeUnion(parents, ps, pe);
        }
    }

    int min = -30000;
    int max = 0;

    for (const auto p : parents) {
        if (p < -1) {
            if (p > min) min = p;
            if (p < max) max = p;
        }
    }

    cout << abs(min) << ' ' << abs(max) << endl;

    return 0;
}