#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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

bool abbreviation(const string &a, const string &b) {
    if (b.size() == 1) {
        if(a.size() < 1) return false;
        int count = 0;
        for (const auto c : a) if (isupper(c)) {
            count++;
            if (count == 2) return false;
        }

        for (size_t i = 0; i < a.size(); i++) {
            if (toupper(a[i]) == b[0]) {
                string tmp{ a };
                tmp.erase(i, 1);

                bool allLower = true;
                for (const auto c : tmp) if (isupper(c)) {
                    allLower = false;
                    break;
                }
                if (allLower) return true;
            }
        }

        return false;
    }

    for (size_t i = 0; i < a.size() - b.size() + 1; i++) {
        if (toupper(a[i]) != b[0] && isupper(a[i])) return false;
        if (toupper(a[i]) == b[0] && abbreviation(a.substr(i + 1), b.substr(1))) return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n;
    stringstream stream{ reader->readLine() };
    stream >> n;

    while (n--) {
        const string a = reader->readLine();
        const string b = reader->readLine();
        cout << (abbreviation(a, b) ? "YES" : "NO") << endl;
    }

    return 0;
}
