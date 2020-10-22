#include <fstream>
#include <limits>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

const int MaxSquare = 100;

struct Square{
    bool visited = false;
    int level = -1,
    ladderTo = -1,
    snakeTo = -1;
};

// Complete the quickestWayUp function below.
int quickestWayUp(vector<vector<int>> ladders, vector<vector<int>> snakes) {
    vector<Square> squares{MaxSquare};

    for(auto& ladder : ladders){
        squares[ladder[0]].ladderTo = ladder[1];
    }

    for(auto& snake : snakes){
        squares[snake[0]].snakeTo = snake[1];
    }

    list<int> squaresToCheck{};
    squaresToCheck.push_back(0);

    squares[0].visited = true;
    squares[0].level = 0;

    do{
        int currentSquareId = squaresToCheck.front();
        squaresToCheck.pop_front();

        for(int i = 1; i <= 6 && currentSquareId + i < 100;  i++){
            int neighborId = currentSquareId + i;
            if(squares[neighborId].ladderTo != -1) neighborId = squares[neighborId].ladderTo;
            else if(squares[neighborId].snakeTo != -1) neighborId = squares[neighborId].snakeTo;

            if(false == squares[neighborId].visited){
                squares[neighborId].visited = true;
                squares[neighborId].level = squares[currentSquareId].level + 1;
                squaresToCheck.push_back(neighborId);
            }
        }
    }
    while(false == squaresToCheck.empty());

    return squares[MaxSquare - 1].level;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> ladders(n);
        for (int i = 0; i < n; i++) {
            ladders[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> ladders[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int m;
        cin >> m;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> snakes(m);
        for (int i = 0; i < m; i++) {
            snakes[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> snakes[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = quickestWayUp(ladders, snakes);

        cout << result << "\n";
    }

    return 0;
}
