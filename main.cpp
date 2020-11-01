#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
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

    cout << kruskals() << endl;

    return 0;
}

uint64_t kruskals() {
    uint64_t cost = 0;
    unordered_set<int> nodesOfMST;
    unordered_set<int> edgesOfMST;

    for (int i = 0; edgesOfMST.size() < n - 1; i++) {
        bool addEdge = false;
        if (nodesOfMST.find(edges[i].start) != nodesOfMST.end() and
            nodesOfMST.find(edges[i].end) != nodesOfMST.end()) {
            if (!inTheSameComponent(edges[i].start, edges[i].end, edgesOfMST)) addEdge = true;
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
    vector<vector<int>> adjList(n);
    for (auto edgeId : edgesOfMST) {
        adjList[edges[edgeId].start - 1].push_back(edges[edgeId].end - 1);
        adjList[edges[edgeId].end - 1].push_back(edges[edgeId].start - 1);
    }

    vector<bool> visited(n);
    list<int> nodesToCheck{one - 1};
    visited[one - 1] = true;

    while (!nodesToCheck.empty()) {
        int currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();
        for (auto neighbor : adjList[currentNode]) {
            if (neighbor == other - 1) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                nodesToCheck.push_back(neighbor);
            }
        }
    }

    return false;
}