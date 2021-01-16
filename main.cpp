#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
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

struct Edge {
    const int a, b;
    const unsigned cost;
    Edge(const int a, const int b, const unsigned c) : a(a), b(b), cost(c) {}
    int to(const int from) { return from == a ? b : a; }
};

struct Node {
    bool visited;
    vector<shared_ptr<Edge>> edges;
};

int N, M, A, B;
vector<Node> nodes;
vector<unsigned> eliminated;

bool reachableWOBit_i(const unsigned i);
bool isEdgeEliminated(const Edge& e);

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };
    stream >> N >> M;

    int maxCost = 0;
    nodes.resize(N);
    for (int i = 0; i < M; i++) {
        stream = stringstream{ reader->readLine() };
        int a, b, cost;
        stream >> a >> b >> cost;

        if (maxCost < cost) maxCost = cost;
        
        auto edge = make_shared<Edge>(a - 1, b - 1, cost);
        nodes[a - 1].edges.push_back(edge);
        nodes[b - 1].edges.push_back(edge);
    }

    stream = stringstream{ reader->readLine() };
    stream >> A >> B;
    A--;
    B--;

    uint16_t penalty = 0;
    bool connected = false;
    for (int i = log2(maxCost) + 1; i >= 0; i--) {
        if (!reachableWOBit_i(i)) penalty += (1 << i);
        else connected = true;
    }

    cout << (connected ? penalty : -1);
}

bool reachableWOBit_i(const unsigned i) {
    for (auto& node : nodes) node.visited = false;

    queue<int> nodesToCheck;
    nodesToCheck.push(A);
    nodes[A].visited = true;

    while (!nodesToCheck.empty()) {
        int current = nodesToCheck.front();
        nodesToCheck.pop();

        for (auto& edge : nodes[current].edges) {
            int neighbor = edge->to(current);
            if ((edge->cost & (1 << i)) == 0 && !isEdgeEliminated(*edge)) {
                if (!nodes[neighbor].visited) {
                    if (neighbor == B) {
                        eliminated.push_back(i);
                        return true;
                    }
                    nodes[neighbor].visited = true;
                    nodesToCheck.push(neighbor);
                }
            }
        }
    }
    return false;
}

bool isEdgeEliminated(const Edge& e) {
    for (auto i : eliminated) if ((e.cost & (1 << i))) return true;
    return false;
}