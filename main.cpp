#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

vector<uint64_t> heights;
unordered_map<string, uint64_t> cache;

uint64_t getMinHeight(const uint64_t start, const uint64_t end) {
    auto minHeight = heights[start];
    for (size_t i = start; i <= end; i++) if (minHeight > heights[i]) minHeight = heights[i];
    return minHeight;
}

uint64_t getArea(const uint64_t start, const uint64_t end) {
    return getMinHeight(start, end) * (end - start + 1);
}

uint64_t getMaxArea(const uint64_t start, const uint64_t end) {
    const string key = to_string(start) + '_' + to_string(end);
    const auto cachedValue = cache.find(key);
    if (cachedValue != cache.end()) return cachedValue->second;

    if (start == end) return heights[start];
    const auto maxArea = max(max(getArea(start, end), getMaxArea(start + 1, end)), max(getMaxArea(start, end - 1), getArea(start, end)));
    cache.insert({ key, maxArea });

    return maxArea;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    uint64_t n;
    stringstream stream{ reader->readLine() };
    stream >> n;
    
    heights.resize(n);
    stream = stringstream{ reader->readLine() };
    for (auto& h : heights) stream >> h;

    cout << getMaxArea(0, n - 1);

    return 0;
}
