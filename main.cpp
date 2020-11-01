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
    Reader() = default;
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
    ConsoleReader() = default;
    string readLine() override {
        string line;
        getline(cin, line);
        return line;
    }
};
}  // namespace reader

using namespace reader;

struct Edge {
    int start, end, weight;
    Edge() = default;
    Edge(int s, int e, int w) : start(s), end(e), weight(w){};
};

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{reader->readLine()};
    int n, m;
    stream >> n >> m;

    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int start, end, weight;
        stream = stringstream{reader->readLine()};
        stream >> start >> end >> weight;
        edges.emplace_back(start, end, weight);
    }

    sort(edges.begin(), edges.end(), [](const Edge &lhs, const Edge &rhs) { return lhs.weight < rhs.weight; });

    // for (auto &edge : edges) cout << edge.start << '-' << edge.end << '-' << edge.weight << endl;

    return 0;
}