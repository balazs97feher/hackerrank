#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include <sstream>
#include <unordered_map>
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

    auto last_ranked = unique(ranked.begin(), ranked.end());
    ranked.erase(last_ranked, ranked.end());

    unordered_map<int, int> cache;
    vector<int> ranks;
    ranks.reserve(m);

    vector<int> ranked_copy_inv(ranked.rbegin(), ranked.rend());
    auto where = ranked_copy_inv.begin();

    for (auto score : player) {
        auto cached = cache.find(score);
        if (cached != cache.end()) {
            ranks.push_back(cached->second);
            continue;
        }

        where = upper_bound(where, ranked_copy_inv.end(), score);

        int place = ranked_copy_inv.end() - where + 1;
        ranks.push_back(place);
        cache.insert({ score, place });
    }

    for (auto rank : ranks) cout << rank << endl;

    return 0;
}
