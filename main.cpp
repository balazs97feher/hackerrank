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
    uint32_t aCount{ 0 }, bCount{ 0 };

    for (size_t i = 0; i < necklace.size(); i++) {
        if (necklace[i] == 'a') aCount++;
        else if (necklace[i] == 'b') bCount++;
    }

    string_view sectionOfALength(necklace.data(), aCount);
    string_view sectionOfBLength(&necklace.data()[aCount], bCount);
    string_view sectionOfOne(&necklace.data()[aCount + bCount], 1);

    string extendedNecklace{ necklace };
    extendedNecklace.append(sectionOfALength).append(sectionOfBLength).append(sectionOfOne);

    vector<uint32_t> aCountUntil(extendedNecklace.size(), 0);
    vector<uint32_t> bCountUntil(extendedNecklace.size(), 0);
    uint32_t accumA{ 0 }, accumB{ 0 };

    for (size_t i = 0; i < extendedNecklace.size(); i++) {
        if (extendedNecklace[i] == 'a') accumA++;
        else if (extendedNecklace[i] == 'b') accumB++;

        aCountUntil[i] = accumA;
        bCountUntil[i] = accumB;
    }

    uint32_t minSwap{ numeric_limits<uint32_t>::max() };

    for (size_t i = 1; i + aCount + bCount < extendedNecklace.size(); i++) {
        const auto aCountInSectionA = aCountUntil[i + aCount - 1] - aCountUntil[i - 1];
        const auto bCountInSectionA = bCountUntil[i + aCount - 1] - bCountUntil[i - 1];

        uint32_t bMinSwap = numeric_limits<uint32_t>::max();
        for (size_t j = i + aCount; j + bCount < extendedNecklace.size(); j++) {
            const auto aCountInSectionB = aCountUntil[j + bCount - 1] - aCountUntil[j - 1];
            const auto bCountInSectionB = bCountUntil[j + bCount - 1] - bCountUntil[j - 1];

            uint32_t bSwap{ 0 };
            if (bCountInSectionA >= aCountInSectionB) bSwap = bCount - bCountInSectionB - aCountInSectionB;
            else bSwap = bCount - bCountInSectionA;

            if (bSwap < bMinSwap) bMinSwap = bSwap;
        }

        const auto aSwap = aCount - aCountInSectionA;
        if (aSwap + bMinSwap < minSwap) minSwap = aSwap + bMinSwap;
    }

    return minSwap;
}

int main(int argc, char* argv[]) {
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
