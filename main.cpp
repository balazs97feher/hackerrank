#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
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

struct Coordinates {
    Coordinates() = default;
    Coordinates(const size_t row, const size_t col) : row(row), col(col) {}
    size_t row, col;

};

ostream& operator<<(ostream& os, const Coordinates coordinates) {
    os << "{" << coordinates.row << "; " << coordinates.col << "}";
    return os;
}

template<size_t N>
void drawSnippet(const char(&snippet)[N][N]) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            cout << snippet[i][j];
        }
        cout << endl;
    }
}

void invert(char (&snippet)[3][3], const size_t row, const size_t col) {
    if (snippet[row][col] == 'w') snippet[row][col] = 'b';
    else snippet[row][col] = 'w';
    
    
    if (row < 2) {
        if (snippet[row + 1][col] == 'w') snippet[row + 1][col] = 'b';
        else snippet[row + 1][col] = 'w';
    }

    if (col < 2) {
        if (snippet[row][col + 1] == 'w') snippet[row][col + 1] = 'b';
        else snippet[row][col + 1] = 'w';
    }
        
    if (row < 2 && col < 2) {
        if (snippet[row + 1][col + 1] == 'w') snippet[row + 1][col + 1] = 'b';
        else snippet[row + 1][col + 1] = 'w';
    }
}

bool patternsMatch(const char(&pattern)[2][2], const char(&snippet)[3][3]) {
    if (pattern[0][0] != snippet[1][1]) return false;
    if (pattern[1][0] != snippet[2][1]) return false;
    if (pattern[0][1] != snippet[1][2]) return false;
    if (pattern[1][1] != snippet[2][2]) return false;

    return true;
}

template<size_t N>
void paintItWhite(char (&snippet)[N][N]) {
    for (size_t i = 0; i < N; i++) for (size_t j = 0; j < N; j++) snippet[i][j] = 'w';
}

using Generator = vector<Coordinates>;

vector<vector<Generator>> generators(16);

vector<Generator> findPatternGenerators(const size_t pattern) {
    char drawnPattern[2][2];
    paintItWhite(drawnPattern);

    if ((1 << 0) & pattern) drawnPattern[0][0] = 'b';
    if ((1 << 1) & pattern) drawnPattern[0][1] = 'b';
    if ((1 << 2) & pattern) drawnPattern[1][0] = 'b';
    if ((1 << 3) & pattern) drawnPattern[1][1] = 'b';

    cout << "--------------------------------------" << endl;
    drawSnippet(drawnPattern);
    cout << endl;

    vector<Generator> patternGenerators;

    for (size_t i = 0; i < 512; i++) {
        char snippet[3][3];
        paintItWhite(snippet);

        Generator generator;
        for (size_t j = 0; j < 9; j++) {
            const bool mark = (1 << j) & i;
            if (mark) {
                invert(snippet, j / 3, j % 3);
                generator.emplace_back(j / 3, j % 3);
            }
        }
        if (patternsMatch(drawnPattern, snippet)) {
            patternGenerators.push_back(generator);
            for (const auto c : generator) cout << c << " ";
            cout << endl;
        }
    }

    return patternGenerators;
}

void findGenerators() {
    for (size_t i = 15; i < 16; i++) {
        generators[i] = findPatternGenerators(i);
    }
}

int main(int argc, char *argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    findGenerators();

    return 0;
}
