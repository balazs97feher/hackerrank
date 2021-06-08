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
    if (s.empty()) return true;
    if (s.size() == 1) return false;

    int idx = 1;

    if (pairOf(s[0] == 0)) return false;

    for (size_t idx = 1; idx < s.size(); idx++) {
        if (s[idx] == pairOf(s[0])) {
            const string leftPart = s.substr(1, idx - 1);
            const string rightPart = s.substr(idx + 1, s.size() - idx - 1);

            if (isBalanced(leftPart) && isBalanced(rightPart)) return true;
        }
    }
    
    return false;
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
