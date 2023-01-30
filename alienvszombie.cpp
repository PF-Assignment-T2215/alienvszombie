#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <iomanip> //set width(w)
using namespace std;


void setObject(vector<vector<char>>& map_, int x, int y, char object) 
{
    map_[y - 1][x - 1] = object; //set coordinate for object
}

void randomitem(vector<vector<char>>& map_, int x_, int y_) //for inserting objects in game board
{
   
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'p', 'h', 'r', '<', '>', '^', 'v'};
    int noOfObjects = 13; 
   
    for (int i = 0; i < y_; ++i) //for row
    {
        for (int j = 0; j < x_; ++j) //for column
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void size(int& x_, int& y_) //set size for column and row 
{
    bool size = true;
    while (size)
    {
        cout << "How many columns?: ";
        cin >> x_;
        cout << endl;
        cout << "How many rows?: ";
        cin >> y_;
        cout << endl;

        if ((x_ % 2 == 0 || y_ % 2 == 0)) //when even number entered
        {
            cout << "Please input odd numbers only" << endl;
        }
        else
        {
            size = false;
        }
    }
}

void displayboard(vector<vector<char>>& map_, int x_, int y_) //displayinig game board layout
{
    cout << "  --++--++--++--++--++--++--++--+ " << endl;
    cout << "        = Alien VS Zombie =       " << endl;
    cout << "  --++--++--++--++--++--++--++--+ " << endl;

    for (int i = 0; i < y_; ++i)
    {
        cout << "  ";
        for (int j = 0; j < x_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (y_ - i);

        for (int j = 0; j < x_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    cout << "  ";
    for (int j = 0; j < x_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < x_; ++j)
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
    for (int j = 0; j < x_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}


void movealien(vector<vector<char>>& map_, int& x, int& y, int x_, int y_, char alien) //for alien movement
{  
    char space = ' ';
    string option;
    cout << " up/down/left/right -> "; //ask user to control movemnt through these command
    cin >> option;

    if (option == "up")
    {
        setObject(map_,x,y, space);
        setObject(map_, x, y - 1, alien);
        y = y - 1;
    }
    else if (option == "down")
    {
        setObject(map_,x,y, space);
        setObject(map_, x, y + 1, alien);
        y = y + 1;
    }
    else if (option == "right")
    {
        setObject(map_,x,y, space);
        setObject(map_, x + 1, y, alien);
        x = x + 1;
    }
    else if (option == "left")
    {  
        setObject(map_,x,y, space);
        setObject(map_, x - 1, y, alien);
        x = x - 1;
    }
}

int main()
{
    srand(1); // use this for fixed map_ during testing, 'random' placement
    vector<vector<char>> map_; //declare variable(map_) as vector
    
    int x, y;
    int x_, y_;
    char alien = 'A';

    size(x_, y_); //set vector size

    map_.resize(y_); // create empty rows(the vectors)
    for (int i = 0; i < y_; ++i)
    {
        map_[i].resize(x_); // resize each row
    }

    x = rand() % x_ + 1; //random coordinate for objects
    y = rand() % y_ + 1;

    randomitem(map_, x_, y_); //call function for placement
    //setObject(map_, x, y, alien); //alien placement
    map_ [x_/2+1] [y_/2-1] = alien; ////alien placement at centre
    while (true)
    {
        displayboard(map_, x_, y_);
        movealien(map_, x, y, x_, y_, alien );
    }
}
