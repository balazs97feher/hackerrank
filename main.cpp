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

struct Vertex {
    bool visited;
    int subTreeSize;
};

vector<vector<int>> adjacencyList(const int n, const vector<vector<int>> &edges);
int evenForest(const int n, const vector<vector<int>> &edges);
int DFS(const int root, vector<Vertex> &vertices, const vector<vector<int>> &edges);

static int numberOfRemovedEdges = 0;

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n, m;
    stringstream stream{reader->readLine()};
    stream >> n >> m;

    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].resize(2);
        stream = stringstream(reader->readLine());
        stream >> edges[i][0] >> edges[i][1];
    }

    evenForest(n, edges);

    return 0;
}

vector<vector<int>> adjacencyList(const int n, const vector<vector<int>> &edges) {
    vector<vector<int>> adjList(n);

    for (auto &edge : edges) {
        adjList[edge[0] - 1].push_back(edge[1] - 1);
        adjList[edge[1] - 1].push_back(edge[0] - 1);
    }

    return adjList;
}

int evenForest(const int n, const vector<vector<int>> &edges) {
    auto adjList = adjacencyList(n, edges);
    vector<Vertex> vertices(n);

    DFS(0, vertices, adjList);

    cout << numberOfRemovedEdges << endl;

    return 0;
}

int DFS(const int root, vector<Vertex> &vertices, const vector<vector<int>> &adjList) {
    int subTreeSize = 1;
    vertices[root].visited = true;

    for (auto neighbor : adjList[root]) {
        if (vertices[neighbor].visited == false) {
            int neighborSubTreeSize = DFS(neighbor, vertices, adjList);
            if (neighborSubTreeSize % 2 == 0)
                numberOfRemovedEdges++;
            else
                subTreeSize += neighborSubTreeSize;
        }
    }
    vertices[root].subTreeSize = subTreeSize;

    // cout << "v " << root + 1 << " size " << subTreeSize << endl;
    return subTreeSize;
}
