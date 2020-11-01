#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
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

static vector<Edge> edges;
static int n;

uint64_t kruskals();
bool inTheSameComponent(const int one, const int other, const unordered_set<int> &edgesOfMST);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{reader->readLine()};
    int m;
    stream >> n >> m;

    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int start, end, weight;
        stream = stringstream{reader->readLine()};
        stream >> start >> end >> weight;
        edges.emplace_back(start, end, weight);
    }

    sort(edges.begin(), edges.end(), [](const Edge &lhs, const Edge &rhs) { return lhs.weight < rhs.weight; });

    // for (auto &edge : edges) cout << edge.start << '-' << edge.end << '-' << edge.weight << endl;

    cout << kruskals() << endl;

    return 0;
}

uint64_t kruskals() {
    uint64_t cost = 0;
    unordered_set<int> nodesOfMST;
    unordered_set<int> edgesOfMST;

    for (int i = 0; nodesOfMST.size() < n; i++) {
        bool addEdge = false;
        if (nodesOfMST.find(edges[i].start) != nodesOfMST.end() and
            nodesOfMST.find(edges[i].end) != nodesOfMST.end()) {
            if (inTheSameComponent(edges[i].start, edges[i].end, edgesOfMST)) addEdge = true;
        } else
            addEdge = true;

        if (addEdge) {
            cost += edges[i].weight;
            edgesOfMST.insert(i);
            nodesOfMST.insert(edges[i].start);
            nodesOfMST.insert(edges[i].end);
        }
    }

    return cost;
}

bool inTheSameComponent(const int one, const int other, const unordered_set<int> &edgesOfMST) {
    vector<bool> visited(n);
    vector<vector<int>> adjList(n);

    // for (auto)

    return false;
}