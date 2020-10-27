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

list<unordered_set<uint32_t>>::iterator findAstronaut(uint32_t astronaut, list<unordered_set<uint32_t>> &countries);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{reader->readLine()};
    int n, p;
    stream >> n >> p;

    list<unordered_set<uint32_t>> countries;
    vector<bool> belongsToACountry(n);

    for (int i = 0; i < p; i++) {
        stream = stringstream{reader->readLine()};
        uint32_t astronaut1, astronaut2;
        stream >> astronaut1 >> astronaut2;

        auto country = findAstronaut(astronaut1, countries);
        if (country != countries.end()) {
            country->insert(astronaut2);
        } else {
            country = findAstronaut(astronaut2, countries);
            if (country != countries.end()) {
                country->insert(astronaut1);
            } else {
                countries.emplace_back(unordered_set<uint32_t>{astronaut1, astronaut2});
            }
        }
        belongsToACountry[astronaut1] = true;
        belongsToACountry[astronaut2] = true;
    }

    uint32_t lonerCount = count(belongsToACountry.begin(), belongsToACountry.end(), false);

    for (auto &country : countries) {
        for (auto astronaut : country) cout << astronaut << ' ';
        cout << endl;
    }
    cout << lonerCount << endl;

    return 0;
}

list<unordered_set<uint32_t>>::iterator findAstronaut(uint32_t astronaut, list<unordered_set<uint32_t>> &countries) {
    for (auto country = countries.begin(); country != countries.end(); country++)
        if (country->find(astronaut) != country->end()) return country;

    return countries.end();
}