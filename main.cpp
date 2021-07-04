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

class Heap {
public:
    Heap() : elements({ 0 }) { }
    int64_t peekMin() {
        return elements[1];
    }
    void addElement(const int64_t elem) {
        elements.push_back(elem);
        int parent, prevPos = elements.size() - 1;
        while ((parent = prevPos / 2) > 0) {
            if (elements[parent] > elem) {
                swap(elements[parent], elements[prevPos]);
                prevPos = parent;
            }
            else break;
        }
    }
    void removeElement(const int64_t elem) {
        int idx = findIndex(elem);

        if (idx == elements.size() - 1) {
            elements.pop_back();
            return;
        }

        swap(elements[idx], elements[elements.size() - 1]);
        elements.pop_back();

        bool inPlace = false;
        while (!inPlace) {
            if (elements.size() >= (2 * idx + 2)) {
                if (elements[2 * idx] < elements[2 * idx + 1]) {
                    swap(elements[2 * idx], elements[idx]);
                    idx = 2 * idx;
                }
                else {
                    swap(elements[2 * idx + 1], elements[idx]);
                    idx = 2 * idx + 1;
                }
            }
            else if (elements.size() == (2 * idx + 1)) {
                swap(elements[2 * idx], elements[idx]);
                idx = 2 * idx;
            }
            else inPlace = true;
        }
    }

private:
    vector<int64_t> elements;

    int findIndex(const int64_t elem) {
        for (int i = 1; i < elements.size(); i++) if (elements[i] == elem) return i;
        return -1;
    }
};

int main(int argc, char* argv[]) {
    unique_ptr<Reader> reader;
    if (argc == 2)
        reader = unique_ptr<FileReader>(new FileReader(argv[1]));
    else
        reader = unique_ptr<ConsoleReader>(new ConsoleReader);

    int n;
    stringstream stream{ reader->readLine() };
    stream >> n;

    Heap heap;

    while (n--) {
        stream = stringstream{ reader->readLine() };
        int op;
        int64_t x;
        stream >> op;
        switch (op)
        {
        case 1:
            stream >> x;
            heap.addElement(x);
            break;
        case 2:
            stream >> x;
            heap.removeElement(x);
            break;
        case 3:
            cout << heap.peekMin() << endl;
        }
    }

    return 0;
}
