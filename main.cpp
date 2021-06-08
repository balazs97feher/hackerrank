#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <stack>

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

char pairOf(const char c) {
    switch (c)
    {
    case '[':
        return ']';
    case '(':
        return ')';
    case '{':
        return '}';
    }

    return 0;
}

bool isBalanced(const string s) {
    stack<char> brackets;

    for (const auto b : s) {
        if (pairOf(b)) brackets.push(b);
        else {
            if (brackets.empty()) return false;
            if (pairOf(brackets.top()) == b) brackets.pop();
            else return false;
        }
    }

    return brackets.empty();
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    size_t n;

    stringstream stream{ reader->readLine() };
    stream >> n;

    while (n--) {
        cout << ( isBalanced(reader->readLine()) ? "YES" : "NO" ) << endl;
    }

    return 0;
}
