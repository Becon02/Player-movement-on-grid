#include <string>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define width 20
#define height 20

class Player
{
public:

    string name;
    int xPos, yPos;
    float speed;
    float rotation;

    Player()
    {
        name = "Default";
        xPos = 0;
        yPos = 0;
        speed = 0.f;
        rotation = 0.f;
    }
};

class Game
{
public:

    Player player[1];

    Game()
    {
        //Values for player 1
        player[0].name = "Becon02";
        player[0].xPos = (width / 2);
        player[0].yPos = (height / 2);
        player[0].rotation = 0.f;
        player[0].speed = 0.5f;
    }
};

void SpaceLine();
void UpdatePosition(Game game);
void DisplayGrid(Game game);
void Color(int typeColor);
void Dead();
void GameDisplay(Game game);
void GamblingState(Game game);

int main()
{
    Game game;

    GameDisplay(game);
}

void SpaceLine()
{
    cout << "--------------------------------------------------------------------------------------\n";
}

void UpdatePosition(Game game)
{
    char keyPress;
    int asciiValue;
    bool keepGoing = true;

    cout << "Move with (w/a/s/d)" << endl;

    while (keepGoing == true)
    {
        keyPress = _getch();
        asciiValue = keyPress;

        //cout << asciiValue << endl;

        switch (asciiValue)
        {
        case 'w':
        {
            if (game.player[0].yPos == 0)
            {
                game.player[0].yPos = 0;
            }
            else
            {
                game.player[0].yPos -= 1;
            }
            break;
        }
        case 'a':
        {
            if (game.player[0].xPos == 0)
            {
                game.player[0].xPos = 0;
            }
            else
            {
                game.player[0].xPos -= 1;
            }
            break;
        }
        case 's':
        {
            if (game.player[0].yPos == (height - 1))
            {
                game.player[0].yPos = (height - 1);
            }
            else
            {
                game.player[0].yPos += 1;
            }
            break;
        }
        case 'd':
        {
            if (game.player[0].xPos == (width - 1))
            {
                game.player[0].xPos = (width - 1);
            }
            else
            {
                game.player[0].xPos += 1;
            }
            break;
        }
        default:
            break;
        }

        system("CLS");

        SpaceLine();

        DisplayGrid(game);

        cout << "Player position is (" << game.player[0].xPos << ", " << game.player[0].yPos << ")" << endl;
    }

    SpaceLine();
}

void DisplayGrid(Game game)
{
    char GameMap[width][height];

    int xPos = game.player[0].xPos;
    int yPos = game.player[0].yPos;


    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            GameMap[x][y] = '.';


            GameMap[xPos][yPos] = 1;

            //Falls in spike

            if (game.player[0].xPos == 4 && game.player[0].yPos == 7)
            {

                Dead();

                SpaceLine();

                exit(0);
            }
            else
            {
                GameMap[4][7] = 94;
            }

            //Falls in gambling

            if (game.player[0].xPos == 9 && game.player[0].yPos == 13)
            {
                GamblingState(game);

            }
            else
            {
                GameMap[9][13] = 36;
            }


            cout << GameMap[x][y] << " ";
        }
        cout << endl;
    }

    SpaceLine();
}

void Color(int typeColor)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, typeColor);
}

void Dead()
{
    Color(4);
    cout << "You died" << endl;
    Color(7);

    SpaceLine();

    exit(0);
}

void GameDisplay(Game game)
{
    SpaceLine();

    DisplayGrid(game);

    UpdatePosition(game);
}

void GamblingState(Game game)
{
    string Answer;
    bool understandRules = false;
    bool correctButton = false;
    bool randNum = false;

    char input;
    int asciValue;

    while (understandRules == false)
    {
        understandRules = false;


        cout << "You have fallen in the gambling box." << endl;
        cout << "I will throw a dice. If the dice is greater than 5 you will leave this place." << endl;
        cout << "If not you will die." << endl;

        cout << "Did you understood the question? (Yes/No)" << endl;
        cin >> Answer;


        if (Answer == "Yes")
        {
            cout << "Perfect then throw the dice." << endl;
            understandRules = true;
        }
        else if (Answer == "No")
        {
            understandRules = false;
        }
        else
        {
            cout << "Make sure you type it correctly." << endl;
        }
    }

    SpaceLine();



    while (correctButton == false)
    {
        cout << "Press w to throw the dice." << endl;
        input = _getch();
        asciValue = input;
        correctButton = false;

        if (asciValue == 'w')
        {
            correctButton = true;

            int randNum = rand() % (10 + 1);

            system("CLS");

            cout << "The dice number is !! ";

            if (randNum > 5)
            {
                Color(10);
                cout << randNum;
                Color(7);

                cout << " !!" << endl;
            }
            else
            {
                Color(4);
                cout << randNum;
                Color(7);

                cout << " !!" << endl;
            }

            if (randNum > 5)
            {
                game.player[0].xPos = 10;
                game.player[0].yPos = 10;

                GameDisplay(game);

            }
            else
            {
                Dead();
            }
        }
        else
        {
            correctButton = false;
            cout << "You didnt click the correct button." << endl;
        }
    }
}
