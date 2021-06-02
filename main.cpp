#include <fstream>
#include <iostream>
#include <memory>
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

struct Node {
    Node() : endOfName(false), wordCount(0) {
        for (auto& child : children) child = nullptr;
    }

    bool endOfName;
    Node* children[26];
    int wordCount;
};

void addName(Node* trie, const string& name) {
    Node* iter = trie;

    for (const auto letter : name) {
        if (iter->children[letter - 97] == nullptr) {
            iter->children[letter - 97] = new Node;
        }
        iter = iter->children[letter - 97];
        iter->wordCount++;
    }

    iter->endOfName = true;
}

int partialMatchCount(Node* trie, const string& partial) {
    Node* iter = trie;

    for (const auto letter : partial) {
        if (iter != nullptr) {
            iter = iter->children[letter - 97];
        }
    }

    if (!iter) return 0;
    else return iter->wordCount;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int q;

    stringstream stream{ reader->readLine() };
    stream >> q;

    Node* trie = new Node;

    while (q-- > 0) {
        stream = stringstream{ reader->readLine() };
        string query, name;
        stream >> query >> name;

        if (query == "add") addName(trie, name);
        else cout << partialMatchCount(trie, name) << endl;
    }

    return 0;
}
