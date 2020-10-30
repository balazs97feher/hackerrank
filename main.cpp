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

    return 0;
}