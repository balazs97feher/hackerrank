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

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    priority_queue<uint32_t> smaller;
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> greater;

    uint32_t n, a, first, second;
    stringstream stream{ reader->readLine() };
    stream >> n;

    stream = stringstream{ reader->readLine() };
    stream >> first;
    cout << first << endl;
    stream = stringstream{ reader->readLine() };
    stream >> second;
    cout << (float(first) + second) / 2.0 << endl;

    if (first > second) {
        greater.push(first);
        smaller.push(second);
    }
    else {
        greater.push(second);
        smaller.push(first);
    }
    n -= 2;

    while (n--) {
        stream = stringstream{ reader->readLine() };
        stream >> a;
        
        if (a > smaller.top()) greater.push(a);
        else smaller.push(a);

        if (smaller.size() > greater.size() + 1) {
            greater.push(smaller.top());
            smaller.pop();
        }
        else if (greater.size() > smaller.size() + 1) {
            smaller.push(greater.top());
            greater.pop();
        }
        
        if (smaller.size() == greater.size()) cout << (float(smaller.top()) + greater.top()) / 2.0 << endl;
        else if (smaller.size() > greater.size()) cout << smaller.top() << endl;
        else cout << greater.top() << endl;
    }

    return 0;
}
