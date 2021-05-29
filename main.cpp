#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

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

auto findSet(list<unordered_set<uint16_t>>& sets, const uint16_t s) {
    for (auto it = sets.begin(); it != sets.end(); it++) {
        if (it->find(s) != it->end()) return it;
    }

    return sets.end();
}

void store(list<unordered_set<uint16_t>>& sets, const uint16_t s, const uint16_t e) {
    auto setOfS = findSet(sets, s);
    auto setOfE = findSet(sets, e);

    if (setOfE == sets.end() && setOfS == sets.end()) {
        sets.push_back({ s, e });
    }
    else if (setOfE == sets.end()) {
        setOfS->insert(e);
    }
    else if (setOfS == sets.end()) {
        setOfE->insert(s);
    }
    else if (setOfS != setOfE) {
        for (const auto elem : *setOfE) setOfS->insert(elem);
        sets.erase(setOfE);
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

    list<unordered_set<uint16_t>> sets;

    while (n-- > 0) {
        uint16_t s, e;
        stream = stringstream{ reader->readLine() };
        stream >> s >> e;

        store(sets, s, e);
    }

    uint16_t min = 30000;
    uint16_t max = 0;

    for (const auto& s : sets) {
        const auto setSize = s.size();
        if (setSize > max) max = setSize;
        if (setSize < min && setSize > 1) min = setSize;
    }

    cout << min << ' ' << max << endl;

    return 0;
}
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

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

auto findSet(list<unordered_set<uint16_t>>& sets, const uint16_t s) {
    for (auto it = sets.begin(); it != sets.end(); it++) {
        if (it->find(s) != it->end()) return it;
    }

    return sets.end();
}

void store(list<unordered_set<uint16_t>>& sets, const uint16_t s, const uint16_t e) {
    auto setOfS = findSet(sets, s);
    auto setOfE = findSet(sets, e);

    if (setOfE == sets.end() && setOfS == sets.end()) {
        sets.push_back({ s, e });
    }
    else if (setOfE == sets.end()) {
        setOfS->insert(e);
    }
    else if (setOfS == sets.end()) {
        setOfE->insert(s);
    }
    else if (setOfS != setOfE) {
        for (const auto elem : *setOfE) setOfS->insert(elem);
        sets.erase(setOfE);
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

    list<unordered_set<uint16_t>> sets;

    while (n-- > 0) {
        uint16_t s, e;
        stream = stringstream{ reader->readLine() };
        stream >> s >> e;

        store(sets, s, e);
    }

    uint16_t min = 30000;
    uint16_t max = 0;

    for (const auto& s : sets) {
        const auto setSize = s.size();
        if (setSize > max) max = setSize;
        if (setSize < min && setSize > 1) min = setSize;
    }

    cout << min << ' ' << max << endl;

    return 0;
}
