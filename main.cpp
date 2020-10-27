#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

namespace reader {
class Reader {
   public:
    Reader() = default;
    virtual string readLine() = 0;
};

class FileReader : public Reader {
    std::ifstream inputFile;

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
}  // namespace reader

using namespace reader;

int32_t findCountries(const uint32_t astronaut, const vector<unordered_set<uint32_t>> &countries);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{reader->readLine()};
    uint32_t n, p;
    stream >> n >> p;

    vector<unordered_set<uint32_t>> countries;
    countries.reserve(n / 2);
    vector<bool> belongsToACountry(n);

    for (int i = 0; i < p; i++) {
        stream = stringstream{reader->readLine()};
        uint32_t astronaut1, astronaut2;
        stream >> astronaut1 >> astronaut2;

        belongsToACountry[astronaut1] = true;
        belongsToACountry[astronaut2] = true;

        auto homeCountry1 = findCountries(astronaut1, countries);
        auto homeCountry2 = findCountries(astronaut2, countries);

        if (homeCountry1 == -1 && homeCountry2 == -1) {
            countries.emplace_back(unordered_set<uint32_t>{astronaut1, astronaut2});
        } else if (homeCountry1 == -1) {
            countries[homeCountry2].insert(astronaut1);
        } else if (homeCountry2 == -1) {
            countries[homeCountry1].insert(astronaut2);
        } else {
            for (auto astronaut : countries[homeCountry2]) countries[homeCountry1].insert(astronaut);
            countries[homeCountry2].clear();
        }
    }
    int32_t lonerCount = count(belongsToACountry.begin(), belongsToACountry.end(), false);

    vector<uint32_t> populations(countries.size() + 1);
    for (int i = 0; i < countries.size(); i++) populations[i] = countries[i].size();
    populations[countries.size()] = lonerCount;

    uint64_t matchCount = 0;
    for (uint32_t i = 0; i < populations.size() - 1; i++) {
        for (uint32_t j = i + 1; j < populations.size(); j++) {
            matchCount += populations[i] * populations[j];
        }
    }
    matchCount += (lonerCount * (lonerCount - 1)) / 2;

    cout << matchCount << endl;

    return 0;
}

int32_t findCountries(const uint32_t astronaut, const vector<unordered_set<uint32_t>> &countries) {
    for (int32_t i = 0; i < countries.size(); i++) {
        if (countries[i].find(astronaut) != countries[i].end()) return i;
    }

    return -1;
}