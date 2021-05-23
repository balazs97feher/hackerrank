#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

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

class Node {
public:
    Node(const int id) : id(id), left(nullptr), right(nullptr) {}
    int id;
    Node* left;
    Node* right;
};

vector<unique_ptr<Node>> buildBinaryTree(vector<vector<int>> indexes) {
    vector<unique_ptr<Node>> tree;
    tree.push_back(make_unique<Node>(1));

    queue<Node*> toBeGrown;
    toBeGrown.push(tree.back().get());

    for (int i = 0; i < indexes.size(); i++) {
        auto nextNode = toBeGrown.front();
        toBeGrown.pop();
        if (indexes[i][0] == -1) nextNode->left = nullptr;
        else {
            tree.push_back(make_unique<Node>(indexes[i][0]));
            nextNode->left = tree.back().get();
            toBeGrown.push(nextNode->left);
        }
        if (indexes[i][1] == -1) nextNode->right = nullptr;
        else {
            tree.push_back(make_unique<Node>(indexes[i][1]));
            nextNode->right = tree.back().get();
            toBeGrown.push(nextNode->right);
        }
    }

    return tree;
}

void traverseSubtree(vector<int>& order, Node* root) {
    if (!root) return;

    order.push_back(root->id);
    traverseSubtree(order, root->left);
    traverseSubtree(order, root->right);
}

vector<int> traverseInOrder(const vector<unique_ptr<Node>>& tree) {
    vector<int> order;

    traverseSubtree(order, tree[0]->left);
    order.push_back(tree[0]->id);
    traverseSubtree(order, tree[0]->right);

    return order;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int nodeCount, queryCount;
    stringstream stream{ reader->readLine() };
    stream >> nodeCount;

    vector<vector<int>> indices(nodeCount);

    for (int i = 0; i < nodeCount; i++) {
        indices[i].resize(2);
        stream = stringstream{ reader->readLine() };
        stream >> indices[i][0] >> indices[i][1];
    }

    stream = stringstream{ reader->readLine() };
    stream >> queryCount;
    vector<int> queries(queryCount);

    for (auto& q : queries) {
        stream = stringstream{ reader->readLine() };
        stream >> q;
    }

    auto tree = buildBinaryTree(indices);

    for (auto e : traverseInOrder(tree)) cout << e << endl;

    return 0;
}
