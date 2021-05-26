#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
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

uint64_t getMaxArea(const vector<uint64_t> &heights, const int64_t startIndex) {
    auto index = startIndex + 1;
    auto area = heights[startIndex];
    
    while (index < heights.size() && heights[index] >= heights[startIndex]) {
        area += heights[startIndex];
        index++;
    }

    index = startIndex - 1;
    while (index >= 0 && heights[index] >= heights[startIndex]) {
        area += heights[startIndex];
        index--;
    }

    return area;
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
    
    vector<uint64_t> heights;
    heights.resize(n);

    auto compare = [&heights](const int64_t lhs, const int64_t rhs) {
        return heights[lhs] < heights[rhs];
    };
    priority_queue < int64_t, vector<int64_t>, decltype(compare)> heightQueue(compare);

    stream = stringstream{ reader->readLine() };
    for (size_t i = 0; i < n; i++)
    {
        stream >> heights[i];
        heightQueue.push(i);
    }

    uint64_t maxArea = 0;
    while (!heightQueue.empty()) {
        const auto startIndex = heightQueue.top();
        heightQueue.pop();
        const auto area = getMaxArea(heights, startIndex);
        if (area > maxArea) maxArea = area;
    }

    cout << maxArea;

    return 0;
}
