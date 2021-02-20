#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <algorithm>
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

vector<int32_t> cache;
vector<int16_t> numbers;

uint32_t maxSumUntil(const int n)
{
    if (cache[n] != -1) return cache[n];
    if (n == 1) return max<int32_t>(numbers[0], 0);
    if (n == 2) return max<int32_t>(numbers[1], maxSumUntil(1));

    int32_t maxSum = max<int32_t>(numbers[n - 1] + maxSumUntil(n - 2), maxSumUntil(n - 1));
    if (maxSum >= 0) cache[n] = maxSum;
    return maxSum;
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    stringstream ss{ reader->readLine() };
    int n;
    ss >> n;

    numbers.resize(n);
    cache.resize(n+1);

    ss = stringstream{ reader->readLine() };
    for (int i = 0; i < n; i++)
    {
        ss >> numbers[i];
        cache[i] = -1;
    }
    cache[n] = -1;

    cout << maxSumUntil(n);

    return 0;
}
