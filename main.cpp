#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Reader {
   public:
    Reader() {}
    virtual string getLine() = 0;
};

class FileReader : public Reader {
    std::ifstream inputFile;

   public:
    FileReader(const string fileName) : Reader() {
        inputFile = ifstream(fileName);
    }
    string getLine() override {
        string line;
        getline(inputFile, line);
        return line;
    }
};

class ConsoleReader : public Reader {
   public:
    ConsoleReader() : Reader() {}
    string getLine() override {
        string line;
        getline(cin, line);
        return line;
    }
};

vector<string> split_string(string);
vector<vector<int>> mapRoads(int n, vector<vector<int>> &roads);
vector<vector<int>> adjacencyList(int n, vector<vector<int>> &edges);
int nextRoot(int lastRoot, vector<bool> &visited);

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> roads) {
    if (c_lib <= c_road)
        return n * c_lib;

    // calculate number of components with BFS
    list<long> componentSizes;
    auto adjList = adjacencyList(n, roads);
    vector<bool> visited(n);

    list<int> nodesToCheck;
    int root = nextRoot(-1, visited);
    while (root != -1) {
        long componentSize = 0;

        nodesToCheck.push_back(root);
        visited[root] = true;

        do {
            int currentNodeId = nodesToCheck.front();
            nodesToCheck.pop_front();
            componentSize++;

            for (int i = 0; i < adjList[currentNodeId].size(); i++) {
                int neighberId = adjList[currentNodeId][i];
                if (false == visited[neighberId]) {
                    visited[neighberId] = true;
                    nodesToCheck.push_back(neighberId);
                }
            }
        } while (false == nodesToCheck.empty());

        componentSizes.push_back(componentSize);

        root = nextRoot(root, visited);
    }

    long cost = 0;
    for (auto componentSize : componentSizes) {
        cost += (componentSize - 1) * c_road + c_lib;
    }

    return cost;
}

int nextRoot(int lastRoot, vector<bool> &visited) {
    for (size_t i = lastRoot + 1; i < visited.size(); i++)
        if (visited[i] == false)
            return i;

    return -1;
}

vector<vector<int>> adjacencyList(int n, vector<vector<int>> &edges) {
    vector<vector<int>> adjList(n);

    for (auto &edge : edges) {
        adjList[edge[0] - 1].push_back(edge[1] - 1);
        adjList[edge[1] - 1].push_back(edge[0] - 1);
    }

    return adjList;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int q;
    stringstream stream(reader->getLine());
    stream >> q;

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp = reader->getLine();

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> roads(m);
        for (int i = 0; i < m; i++) {
            roads[i].resize(2);

            stringstream stream(reader->getLine());
            for (int j = 0; j < 2; j++) {
                stream >> roads[i][j];
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, roads);

        cout << result << "\n";
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}