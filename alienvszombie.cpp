#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int inputX()
{
    int x;
    cout << "How many columns?: ";
    cin >> x;
    while (x % 2 == 0)
    {
        cout << x << "Please input odd numbers only" << endl;
    }
    return x;
}

int inputY()
{
    int y;
    cout << "How many rows?: ";
    cin >> y;
    if (y % 2 == 0)
        cout << y << "Please input odd numbers only";
    else
        return y;
    // return  y;
}

class GameBoard
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_;

public:
    GameBoard(int dimX = inputX(), int dimY = inputY());
    void init(int dimX, int dimY);
    void display() const;

    int getDimX() const;
    int getDimY() const;

    char getObject(int x, int y) const;
};

char GameBoard::getObject(int x, int y) const
{
    return map_[x][y];
}

int GameBoard::getDimX() const
{
    return dimX_;
}

int GameBoard::getDimY() const
{
    return dimY_;
}

GameBoard::GameBoard(int dimX, int dimY)
{
    init(dimX, dimY);
}

void GameBoard::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'p', 'h', 'r', '^', 'v', '>', '<'};
    int noOfObjects = 13;

    map_.resize(dimY_);
    for (int i = 0; i < dimY_; ++i)

    {
        map_[i].resize(dimX_);
    }

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void GameBoard::display() const
{

    cout << "  --++--++--++--++--++--++--++--+ " << endl;
    cout << "        = Alien VS Zombie =       " << endl;
    cout << "  --++--++--++--++--++--++--++--+ " << endl;

    for (int i = 0; i < dimY_; ++i)
    {
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (dimY_ - i);

        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digits = (j + 1) / 10;
        cout << " ";
        if (digits == 0)
            cout << " ";
        else
            cout << digits;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void dispboard()
{
    GameBoard GameBoard;
    GameBoard.display();
}

int main()
{
    // int getDimX = inputX(); // Takes what the return statement gives
    // int getDimY = inputY();
    srand(time(NULL));
    // return r, c;

    dispboard();
}
