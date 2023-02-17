// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT5L 
// Names: Vaarindran Nyanasegran | Tengku Alyssa Sabrina  | Fadhilah Mohamad Asri
// IDs: 1211103144 | 1211101069 | 1211312193
// Emails: 1211103144@student.mmu.edu.my | 1211101069@student.mmu.edu.my | 1211312193@student.mmu.edu.my
// Phones: 0123401281 | 0129234080 | 0134340114
// ********************************************************* 
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

void dispWelcome() //display welcome banner
{
    cout << "  --++--++--++--++--++--++--++--+ " << endl;
    cout << "   = Welcome to Alien VS Zombie = " << endl;
    cout << "  --++--++--++--++--++--++--++--+ " << endl;
}

void setting(int &x_, int &y_, int &z_)
{
   do
   {
        cout << "Please enter odd numbers only "; //ask user to set board dimension with odd number
        cout << endl; 
        cout << "How many columns? : ";
        cin >> x_;  //max column
        cout << "How many rows? : ";
        cin >> y_; //max row
        cout << endl; 

    } while (x_ % 2 == 0 || y_ % 2 == 0 ); //checking if input are odds num or not
}

void setObject(vector<vector<char>> &map_, int x, int y, char object) //set object in gameboard dimension
{
    map_[y][x] = object;
}

void randomitem(vector<vector<char>> &map_, int x_, int y_) //set game item randomly on gameboard
{
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'p', 'h', 'r', '<', '>', '^', 'v'};
    int noOfObjects = sizeof(objects);

    for (int i = 0; i < y_; ++i) //for row
    {
        for (int j = 0; j < x_; ++j) //for column
        {
            int objNo = rand() % noOfObjects; //generate random total of game object to put in gameboard
            map_[i][j] = objects[objNo]; //put the random object on that position
        }
    }
}

void displayboard(vector<vector<char>> &map_, int x_, int y_) // displaying gameboard layout
{
    system("cls"); //reset output screen
    cout << "  --++--++--++--++--++--++--++--+ " << endl;
    cout << "        = Alien VS Zombie =       " << endl;
    cout << "  --++--++--++--++--++--++--++--+ " << endl;

    for (int i = 0; i < y_; ++i) //setting gameboard border
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
//need more understanding from here
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
}//to here

char getObject(vector<vector<char>> map_, int x, int y) //to check whether alien or zombie met rock/'r' or not
{
    return map_[y][x]; //return char that is in that position to be compare with the condition
}

bool inMap(int x, int y, int x_, int y_) //to check the position alien and zombie whether still in gameboard or not
{
    return ((x < x_) && (y < y_) && (y >= 0) && (x >= 0)); //return true if fulfill all condition
}

void trail(vector<vector<char>> &map_, int x_, int y_) //setting alien trail
{
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'p', 'h', 'r', '<', '>', '^', 'v'};
    int noOfObjects = sizeof(objects);

    for (int i = 0; i < y_; ++i) //for row
    {
        for (int j = 0; j < x_; ++j) //for column
        {
            if (getObject(map_, j, i) == '.') //when there is '.' in map, this code will commence
            {
                int objNo = rand() % noOfObjects; // putting random object on gameboard
                map_[i][j] = objects[objNo];
            }
        }
    }
}

void dashboard(int alien_life, int alien_attack, int zombie_life, int zombie_attack, int zombie_range) //display all attributes
{
    cout << endl;
    cout << "Alien  : Life " << alien_life  << " Attack  " << alien_attack  << endl;
    cout << "Zombie : Life " << zombie_life << " Attack  " << zombie_attack << " Range " << zombie_range << endl;
    cout << endl;
}

//zombie movements
void moveZombie(vector<vector<char>> &map_, int &zombie_x, int &zombie_y, int x_, int y_, char alien, char zombie, int& alien_life, int alien_attack, int zombie_life, int zombie_attack, int zombie_range)
{
    system("cls"); //reset output screen
    displayboard(map_, x_, y_);
    dashboard(alien_life, alien_attack, zombie_life, zombie_attack, zombie_range);

    int option = rand() % 3; //generate random number from zero to 3 to position the zombie
    int next_y = zombie_y;
    int next_x = zombie_x;
    if (option ==  0)
    {
        next_y -= 1; //move upward
    }
    else if (option == 1)
    {
        next_y += 1; //move downward
    }
    else if (option == 2 )
    {
        next_x += 1; //move right
    }
    else if (option == 3)
    {
        next_x -= 1; //move left
    }

    //when get random num = 0 & check zombie still in board & check game object (rock) on next position
    if (option == 0 && inMap(next_x, next_y, x_, y_) && getObject(map_, next_x, next_y) != 'r' ) 
    {
        if (getObject(map_, next_x, next_y) == alien) //zombie attack alien when met on gameboard 
        {
            cout << endl;
            cout << "Zombie attack alien with " << zombie_attack << " damage" << endl;
            cout << endl;
            alien_life -= zombie_attack; //alien_life = alien_life - zombie_attack / alien_life decrease by the value of zombie_attack
        }
        else //proceed to move up if doesn't meet alien
        {
            cout << endl;
            cout << "Zombie move up" << endl;
            cout << endl;
            setObject(map_, zombie_x, zombie_y, ' ');

            zombie_y -= 1;
        }
    }
    else if (option == 1 && inMap(next_x, next_y, x_, y_) && getObject(map_, next_x, next_y) != 'r' ) //fulfill all condition, proceed 
    {
        if (getObject(map_, next_x, next_y) == alien) //zombie attack when met alien
        {
            cout << endl;
            cout << "Zombie attack alien with " << zombie_attack << " damage" << endl;
            cout << endl;
            alien_life -= zombie_attack;
        }
        else  //proceed to move down if doesn't meet alien
        {                
            cout << endl;
            cout << "Zombie move down" << endl;
            cout << endl;
            setObject(map_, zombie_x, zombie_y, ' ');

            zombie_y += 1;
        }
    }
    else if (option == 2 && inMap(next_x, next_y, x_, y_) && getObject(map_, next_x, next_y) != 'r' )
    {
        if (getObject(map_, next_x, next_y) == alien) //zombie attack when met alien
        {
            cout << endl;
            cout << "Zombie attack alien with " << zombie_attack << " damage" << endl;
            cout << endl;
            alien_life -= zombie_attack;
        }
        else  //proceed to move right if doesn't meet alien
        {
            cout << endl;
            cout << "Zombie move right" << endl;
            cout << endl;
            setObject(map_, zombie_x, zombie_y, ' ');

            zombie_x += 1;
        }
    }
    else if (option == 3 && inMap(next_x, next_y, x_, y_) && getObject(map_, next_x, next_y) != 'r')
    {
        if (getObject(map_, next_x, next_y) == alien) //zombie attack when met alien
        {
            cout << endl;
            cout << "Zombie attack alien with " << zombie_attack << " damage" << endl;
            cout << endl;
            alien_life -= zombie_attack;
        }
        else  //proceed to move up if doesn't meet alien 
        {
            cout << endl;
            cout << "Zombie move left" << endl;
            cout << endl;
            setObject(map_, zombie_x, zombie_y, ' ');
            zombie_x -= 1;
        }
    }
    else //when the conditions are not fulfilled
    {
        cout << endl;
        cout << "Zombie forget how to move" << endl; //happens when the 3 conditions are not met
        cout << endl;
    }

    setObject(map_, zombie_x, zombie_y, zombie);
    system("pause");  //pause output screen for processing
}

//alien movement
void moveAlien(vector<vector<char>> &map_, int &x, int &y, int x_, int y_, char alien, int& alien_life, int& alien_attack, int& zombie_life, int zombie_attack, int zombie_range)
{
    int next_y = y;
    int next_x = x;
    bool cont = true;

    char space = ' ';
    string option;
    cout << " up/down/left/right -> "; //ask user to control movement through these command
    cin >> option;

    while (cont) //clear current position before updating new 
    {
        if (option == "up")
        {
            next_y -= 1;
        }
        else if (option == "down")
        {
            next_y += 1;
        }
        else if (option == "right")
        {
            next_x += 1;
        }
        else if (option == "left")
        {
            next_x -= 1;
        }

        if (option == "up" && inMap(next_x, next_y, x_, y_)) //command up and fulfill condition
        {
            if (getObject(map_, next_x, next_y) == '^') //detecting game object
            {
                cout << "Alien will move upward" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "up";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '<') //detecting game object
            {
                cout << "Alien will move left" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "left";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '>') //detecting game object
            {
                cout << "Alien will move right" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "right";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'v') //detecting game object
            {
                cout << "Alien will move down" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "down";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'r') //detecting game object
            {
                cout << "Alien hit rock, Alien will stop" << endl;
                cout << endl;
                break; //break loop
            }
            else if (getObject(map_, next_x, next_y) == 'h') //detecting game object
            {
                cout << "Alien life adds 20" << endl;
                cout << endl;
                alien_life += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'p') //detecting game object
            {
                cout << "Alien hit pod, Zombie life minus 20" << endl;
                cout << endl;
                zombie_life -= 10;
            }
            else if (getObject(map_, next_x, next_y) == '1') //detecting game object
            {
                cout << "Alien deal " << alien_attack << " damage to the zombie" << endl;
                cout << endl;

                zombie_life -= alien_attack;
                if (zombie_life <= 0)
                {
                    cout << "Alien killed zombie" << endl;
                    cout << endl;
                    cont = true;
                }
                else
                {
                    break; //break loop
                }
            }
            
            map_[y][x] = '.';
            y = y - 1;

        }
        else if (option == "down" && inMap(next_x, next_y, x_, y_)) //command down and fulfill condition
        {
          if (getObject(map_, next_x, next_y) == '^') //detecting game object
            {
                cout << "Alien will move upward" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "up";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '<') //detecting game object
            {
                cout << "Alien will move left" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "left";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '>') //detecting game object
            {
                cout << "Alien will move right" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "right";
                alien_attack += 20;

            }
            else if (getObject(map_, next_x, next_y) == 'v') //detecting game object
            {
                cout << "Alien will move down" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "down";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'r') //detecting game object
            {
                cout << "Alien hit rock, Alien will stop" << endl;
                cout << endl;
                break; //break loop
            }
            else if (getObject(map_, next_x, next_y) == 'h') //detecting game object
            {
                cout << "Alien life adds 20" << endl;
                cout << endl;
                alien_life += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'p') //detecting game object
            {
                cout << "Alien hit pod, Zombie life minus 20" << endl;
                cout << endl;
                zombie_life -= 10;
            }
            else if (getObject(map_, next_x, next_y) == '1') //detecting game object
            {
                cout << "Alien deal " << alien_attack << " damage to the zombie" << endl;
                cout << endl;

                zombie_life -= alien_attack;
                if (zombie_life <= 0)
                {
                    cout << "Alien killed zombie" << endl;
                    cout << endl;
                    cont = true;
                }
                else
                {
                    break; //break loop
                }
            }
            map_[y][x] = '.';
            y = y + 1;
        }
        else if (option == "right" && inMap(next_x, next_y, x_, y_)) //command right and fulfill condition
        {
            if (getObject(map_, next_x, next_y) == '^') //detecting game object
            {
                cout << "Alien will move upward" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "up";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '<') //detecting game object
            {
                cout << "Alien will move left" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "left";
                alien_attack += 20;

            }
            else if (getObject(map_, next_x, next_y) == '>') //detecting game object
            {
                cout << "Alien will move right" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "right";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'v') //detecting game object
            {
                cout << "Alien will move down" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "down";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'r') //detecting game object
            {
                cout << "Alien hit rock, Alien will stop" << endl;
                cout << endl;
                break; //break loop
            }
            else if (getObject(map_, next_x, next_y) == 'h') //detecting game object
            {
                cout << "Alien life adds 20" << endl;
                cout << endl;
                alien_life += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'p') //detecting game object
            {
                cout << "Alien hit pod, Zombie life minus 20" << endl;
                cout << endl;
                zombie_life -= 10;
            }
            else if (getObject(map_, next_x, next_y) == '1') //detecting game object
            {
                cout << "Alien deal " << alien_attack << " damage to the zombie" << endl;
                cout << endl;

                zombie_life -= alien_attack;
                if (zombie_life <= 0)
                {
                    cout << "Alien killed zombie" << endl;
                    cout << endl;
                    cont = true;
                }
                else
                {
                    break; //break loop
                }
            }
            map_[y][x] = '.';
            x = x + 1;
        }
        else if (option == "left" && inMap(next_x, next_y, x_, y_)) //command left and fulfill condition
        {
            if (getObject(map_, next_x, next_y) == '^') //detecting game object
            {
                cout << "Alien will move upward" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "up";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '<') //detecting game object
            {
                cout << "Alien will move left" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "left";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == '>') //detecting game object
            {
                cout << "Alien will move right" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "right";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'v') //detecting game object
            {
                cout << "Alien will move down" << endl;
                cout << "Alien attack adds 20" << endl;
                cout << endl;
                option = "down";
                alien_attack += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'r') //detecting game object
            {
                cout << "Alien hit rock, Alien will stop" << endl;
                cout << endl;
                break; //break loop
            }
            else if (getObject(map_, next_x, next_y) == 'h') //detecting game object
            {
                cout << "Alien life adds 20" << endl;
                cout << endl;
                alien_life += 20;
            }
            else if (getObject(map_, next_x, next_y) == 'p') //detecting game object
            {
                cout << "Alien hit pod, Zombie life minus 20" << endl;
                cout << endl;
                zombie_life -= 10;
            }
            else if (getObject(map_, next_x, next_y) == '1') //detecting game object
            {
                cout << "Alien deal " << alien_attack << " damage to the zombie" << endl;
                cout << endl;

                zombie_life -= alien_attack;
                if (zombie_life <= 0)
                {
                    cout << "Alien killed zombie" << endl;
                    cout << endl;
                    cont = true;
                }
                else
                {
                    break; //break loop
                }
            }
            map_[y][x] = '.';
            x = x - 1;
        }
        else //doesn't fulfill condition
        {
            cout << "Alien hit wall" << endl;
            cout << endl;
            cont = false;
        }
         
        map_[y][x] = alien; // update new position
      
        system("pause");
        displayboard(map_, x_, y_);
        dashboard(alien_life, alien_attack, zombie_life, zombie_attack, zombie_range);
    }
    
    trail(map_, x_, y_); //change to random object
}


int main()
{
    dispWelcome();
    srand(time(NULL)); //set random unlimited gameboard pattern
    vector<vector<char>> map_;

    int x, y;
    int zombie_x, zombie_y;
    int x_, y_, z_;
    char alien = 'A';
    char zombie = '1';

    int alien_life = 100; //game character
    int alien_attack;

    int zombie_life = rand() % 20 + 10; //generate random num from zero to 20 / get at least 10 if got zero as random num
    int zombie_attack = rand() % 10 + 5;
    int zombie_range = rand() % 3 + 1;

    setting(x_, y_, z_); //setting board

    map_.resize(y_); // initial vector to creat 2D dynamic array
    for (int i = 0; i < y_; ++i)
    {
        map_[i].resize(x_);
    }

   x = x_ / 2; // alien initial position
   y = y_ / 2;

    do //keep generating new position for zombie if zombie position same as alien
    {
        zombie_x = rand() % x_;
        zombie_y = rand() % y_;
    } while ((zombie_x == x) && (zombie_y == y));

    randomitem(map_, x_, y_); //set game object in map
    setObject(map_, x, y ,alien); //set alien in map
    setObject(map_, zombie_x, zombie_y, zombie); //set zombie in map

    while (true) //when alien hit border, this code will commence
    {
        alien_attack = 0;
        displayboard(map_, x_, y_);
        dashboard(alien_life, alien_attack, zombie_life, zombie_attack, zombie_range);
        moveAlien(map_, x, y, x_, y_, alien, alien_life, alien_attack, zombie_life, zombie_attack, zombie_range);
        moveZombie(map_, zombie_x, zombie_y, x_, y_, alien, zombie,alien_life, alien_attack, zombie_life, zombie_attack, zombie_range);
    }
}
