#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
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

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };
    int n;
    stream >> n;
    vector<int> ranked(n);

    stream = stringstream{ reader->readLine() };
    for (int i = 0; i < n; i++) stream >> ranked[i];

    stream = stringstream{ reader->readLine() };
    int m;
    stream >> m;
    vector<int> player(m);

    stream = stringstream{ reader->readLine() };
    for (int i = 0; i < m; i++) stream >> player[i];

    vector<int> ranks;
    ranks.reserve(m);
    for (auto score : player) {
        vector<int> ranked_copy_inv(ranked.rbegin(), ranked.rend());
        auto where = lower_bound(ranked_copy_inv.begin(), ranked_copy_inv.end(), score);
        auto place = ranked_copy_inv.insert(where, score);

        //auto last = unique(place, ranked_copy_inv.end());
        for (auto a : ranked_copy_inv) cout << a << ' ';
        cout << endl;
    }

    //for (auto rank : ranks) cout << rank << endl;

    return 0;
}
