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

[[ nodiscard ]] uint32_t maxNonDivisibleSubset(const vector<uint32_t> numbers, const uint32_t k) {
    if (k == 1) return 0;

    vector< uint32_t> classes(k, 0);
    for_each(numbers.begin(), numbers.end(), [&classes, k](const uint32_t n) {
        classes[n % k]++;
        });

    if (k == 2) return (classes[0] > 0) + (classes[1] > 0);

    uint32_t maxSize = 0;
    if (classes[0] > 0) maxSize++;
    if (k % 2 == 0 && classes[k / 2] > 0) maxSize++;

    const size_t until = (k % 2 == 0) ? size_t(k / 2) - 1 : size_t(k / 2);

    for (size_t i = 1; i <= until; i++) {
        maxSize += max(classes[i], classes[k - i]);
    }

    return maxSize;
}

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    uint32_t n, k;

    stringstream stream{ reader->readLine() };
    stream >> n >> k;

    vector<uint32_t> numbers(n, 0);

    stream = stringstream{ reader->readLine() };
    for (auto& n : numbers) {
        stream >> n;
    }

    cout << maxNonDivisibleSubset(numbers, k) << endl;

    return 0;
}
