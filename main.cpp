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

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n;
    stringstream ss{ reader->readLine() };
    ss >> n;

    vector<int> scores;
    vector<int> sorted_score_idxs;
    vector<int> candies;

    scores.resize(n);
    sorted_score_idxs.resize(n);
    candies.resize(n);

    for (int i = 0; i < n; i++)
    {
        ss = stringstream{ reader->readLine() };
        ss >> scores[i];
        sorted_score_idxs[i] = i;
    }

    sort(sorted_score_idxs.begin(), sorted_score_idxs.end(),
        [&scores](const int lhs, const int rhs) {return scores[lhs] < scores[rhs];
    });

    uint64_t sum = 0;
   
    for (auto idx : sorted_score_idxs)
    {
        if (idx == 0)
        {
            auto candy = candies[1] + 1;
            if (scores[1] == scores[0] && candies[1] != 0) candy = 1;
            candies[idx] = candy;
            sum += candy;
        }
        else if (idx == n - 1)
        {
            auto candy = candies[idx - 1] + 1;
            if (scores[n - 1] == scores[n - 2] && candies[n - 2] != 0) candy = 1;
            candies[idx] = candy;
            sum += candy;
        }
        else
        {
            auto leftCandydate = candies[idx - 1] + 1;
            if (scores[idx - 1] == scores[idx] && candies[idx - 1] != 0) leftCandydate = 1;

            auto rightCandydate = candies[idx + 1] + 1;
            if (scores[idx + 1] == scores[idx] && candies[idx + 1] != 0) rightCandydate = 1;

            auto candy = max(leftCandydate, rightCandydate);
            candies[idx] = candy;
            sum += candy;
        }
    }

    cout << sum;

    return 0;
}
