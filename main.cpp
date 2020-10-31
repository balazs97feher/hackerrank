#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
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

vector<int> sieveOfEratosthenes(int maxValue);

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int numberOfGames;
    stringstream stream{reader->readLine()};
    stream >> numberOfGames;

    vector<int> values(numberOfGames);
    int maxValue = -1;
    for (int i = 0; i < numberOfGames; i++) {
        stream = stringstream(reader->readLine());
        stream >> values[i];
        if (values[i] > maxValue) maxValue = values[i];
    }

    vector<int> primeNumbers = sieveOfEratosthenes(maxValue);
    // for (auto prime : primeNumbers) cout << prime << ' ';

    return 0;
}

vector<int> sieveOfEratosthenes(int maxValue) {
    vector<int> primes;

    vector<bool> isPrime(maxValue + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i < maxValue + 1; i++) {
        if (isPrime[i] == true) {
            for (int k = 2; k * i <= maxValue + 1; k++) isPrime[k * i] = false;
        }
    }

    for (int i = 2; i <= maxValue + 1; i++)
        if (isPrime[i]) primes.push_back(i);

    return primes;
}