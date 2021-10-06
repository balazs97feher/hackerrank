#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>
#include <limits>

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

uint32_t minSwap(const std::string& necklace) {
    uint32_t aCount = count(necklace.begin(), necklace.end(), 'a');
    string_view section(necklace.data(), aCount);

    string extendedNecklace{ necklace };
    extendedNecklace.append(section);

    vector<uint32_t> aCountUntil(extendedNecklace.size(), 0);
    uint32_t accumA{ 0 };
    for (size_t i = 0; i < extendedNecklace.size(); i++) {
        if (extendedNecklace[i] == 'a') accumA++;
        aCountUntil[i] = accumA;
    }

    uint32_t aMinSwap{ aCountUntil[aCount - 1] };
    uint32_t aMinSwapIdx = 0;
    for (size_t i = 1; i + aCount < aCountUntil.size(); i++) {
        const auto aCountInThisSection = aCountUntil[i + aCount - 1] - aCountUntil[i - 1];
        if (aCountInThisSection < aMinSwap) {
            aMinSwap = aCountInThisSection;
            aMinSwapIdx = i;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream stream{ reader->readLine() };
    string necklace;
    stream >> necklace;

    std::cout << minSwap(necklace) << std::endl;

    return 0;
}
