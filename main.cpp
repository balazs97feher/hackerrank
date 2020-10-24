#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

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

struct Edge {
    int id, from, to;
    uint32_t weight;
    Edge(int id, int f, int t, uint32_t w) : id(id), from(f), to(t), weight(w) {}
    Edge() = default;
};

vector<vector<int>> edgeList(int n, vector<Edge> &edges) {
    vector<vector<int>> eList(n);

    for (int i = 0; i < edges.size(); i++) {
        eList[edges[i].from].push_back(i);
        eList[edges[i].to].push_back(i);
    }

    return eList;
}

int otherEnd(int vertex, Edge &edge) {
    if (edge.from == vertex) return edge.to;
    return edge.from;
}

uint64_t prims(int n, int r, vector<Edge> &edges) {
    vector<vector<int>> eList = edgeList(n, edges);
    unordered_set<int> spanningTreeVertices;
    unordered_set<int> spanningTreeEdges;
    uint64_t MSTCost = 0;

    auto compare = [](const Edge &lhs, const Edge &rhs) { return lhs.weight > rhs.weight; };
    priority_queue<Edge, vector<Edge>, decltype(compare)> connectingEdges(compare);

    int nextNode = r;
    spanningTreeVertices.insert(nextNode);

    while (spanningTreeVertices.size() != n) {
        for (auto edgeId : eList[nextNode])
            if (spanningTreeEdges.find(edgeId) == spanningTreeEdges.end()) connectingEdges.push(edges[edgeId]);

        Edge cheapestEdge;
        do {
            cheapestEdge = connectingEdges.top();
            connectingEdges.pop();
        } while (spanningTreeVertices.find(cheapestEdge.from) != spanningTreeVertices.end() &&
                 spanningTreeVertices.find(cheapestEdge.to) != spanningTreeVertices.end());

        spanningTreeEdges.insert(cheapestEdge.id);
        nextNode = (spanningTreeVertices.find(cheapestEdge.from) == spanningTreeVertices.end()) ? cheapestEdge.from : cheapestEdge.to;
        spanningTreeVertices.insert(nextNode);

        MSTCost += cheapestEdge.weight;
    }

    return MSTCost;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n, m;
    stringstream ss{reader->readLine()};
    ss >> n >> m;

    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        ss = stringstream{reader->readLine()};
        int from, to;
        uint32_t weight;
        ss >> from >> to >> weight;
        edges.emplace_back(i, from - 1, to - 1, weight);
    }

    int r;
    ss = stringstream{reader->readLine()};
    ss >> r;

    auto result = prims(n, r - 1, edges);
    cout << result;

    return 0;
}