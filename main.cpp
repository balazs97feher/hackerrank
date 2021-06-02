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

// T must be a signed type
template <typename T>
class DisjointSet {
public:
    DisjointSet(const size_t setSize) {
        parents.resize(setSize + 1, -1);
    }

    T setSizeOf(const T elem) {
        const auto parent = parentOf(elem);

        return abs(parents[parent]);
    }

    void mergeSets(const T a, const T b) {
        if (a == b) return;

        const auto pa = parentOf(a);
        const auto pb = parentOf(b);

        if (pa < pb) {
            parents[pa] += parents[pb];
            parents[pb] = pa;
        }
        else {
            parents[pb] += parents[pa];
            parents[pa] = pb;
        }
    }

private:
    vector<T> parents;

    T parentOf(const T elem) {
        auto it = elem;
        while (parents[it] >= 0) {
            it = parents[it];
        }

        // collapse find
        if (it != elem) return parents[elem] = it;
        return it;
    }
};

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    size_t n, q;
    stringstream stream{ reader->readLine() };
    stream >> n >> q;

    DisjointSet<int32_t> disjointSet(n);

    char query;
    int32_t i, j;
    while (q-- > 0) {
        stream = stringstream{ reader->readLine() };
        stream >> query;

        if (query == 'Q') {
            stream >> i;
            cout << disjointSet.setSizeOf(i) << endl;
        }
        else {
            stream >> i >> j;
            disjointSet.mergeSets(i, j);
        }
    }

    return 0;
}
