#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

struct Node{
    int level = -1;
    bool visited = false;
};

vector<string> split_string(string);
vector<vector<int>> adjacencyList(int n, vector<vector<int>> edges);

// Complete the bfs function below.
vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
    vector<Node> nodes{n};
    auto adjList = adjacencyList(n, edges);

    
    list<int> nodesToCheck{};
    nodesToCheck.push_back(s - 1);

    nodes[s - 1].visited = true;
    nodes[s - 1].level = 0;

    do{
        int currentNodeId = nodesToCheck.front();
        nodesToCheck.pop_front();

        for(int i = 0; i < adjList[currentNodeId].size(); i++){
            int neighborId = adjList[currentNodeId][i];
            if(false == nodes[neighborId].visited){
                nodes[neighborId].visited = true;
                nodes[neighborId].level = nodes[currentNodeId].level + 6;
                nodesToCheck.push_back(neighborId);
            }
        }
    }
    while(false == nodesToCheck.empty());

    vector<int> result;
    result.reserve(n);
    for(int i = 0; i < n; i++) result.emplace_back(nodes[i].level);
    
    auto rootIt = result.begin();
    advance(rootIt, s - 1);
    result.erase(rootIt);

    return result;
}

vector<vector<int>> adjacencyList(int n, vector<vector<int>> edges){
    vector<vector<int>> adjList(n);
    
    for(auto& edge : edges){
        adjList[edge[0] - 1].push_back(edge[1] - 1);
        adjList[edge[1] - 1].push_back(edge[0] - 1);
    }

    return adjList;
}

int main()
{
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<vector<int>> edges(m);
        for (int i = 0; i < m; i++) {
            edges[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> result = bfs(n, m, edges, s);

        for (int i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
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
