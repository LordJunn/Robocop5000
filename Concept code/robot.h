#ifndef ROBOT_H
#define ROBOT_H

#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "battlefield.h"

using namespace std;

class Robot
{
protected:
    battlefield *gameMap;
    string name;
    char symbol;
    int index;
    int pos[2];
    int lives = 3;
    int kills = 0;
    bool detect = false;
    int detectPos[2] = {0};

public:
    Robot() {}
    virtual void sequence()
    {
        cout << "Sequence not implemented" << endl;
    }
    string getName() const
    {
        return name;
    }
    char getSymbol() const
    {
        return symbol;
    }
    int getX() const
    {
        return pos[0];
    }
    int getY() const
    {
        return pos[1];
    }
    int getLives() const
    {
        return lives;
    }
    int killed()
    {
        return lives--;
    }
    int getIndex() const
    {
        return index;
    }
    void move(int x, int y) // Finished move
    {
        int newX = x;
        int newY = y;
        int arr[2];
        int moves;
        do {
            moves = rand() % 8;
            switch (moves)
            {
            case 0:
                y = 1;
                newX += x;
                break;
            case 1:
                x = 1;
                y = 1;
                newX += x;
                newY += y;
                break;
            case 2:
                x = 1;
                newX += x;
                break;
            case 3:
                x = 1;
                y = -1;
                newX += x;
                newY += y;
                break;
            case 4:
                y = -1;
                newY += y;
                break;
            case 5:
                x = -1;
                y = -1;
                newX += x;
                newY += y;
                break;
            case 6:
                x = -1;
                newX += x;
                break;
            case 7:
                x = -1;
                y = 1;
                newX += x;
                newY += y;
                break;
            default:
                break;
        }
        if (newX < 0 || newX >= gameMap->getWidth() || newY < 0 || newY >= gameMap->getHeight())
            {
                newX = getX();
                newY = getY();
                x = 0;
                y = 0;
            }
        else if (gameMap->checkoccupied(newX, newY) == true)
            {
                newX = getX();
                newY = getY();
                x = 0;
                y = 0;
            }
        } while (x == 0 && y == 0);
        cout << getName() << " has moved to " << newX << "," << newY << endl;
        arr[0] = {newX};
        arr[1] = {newY};
        updateCoords(arr);
        gameMap->changecoords(getIndex(), arr);
    }
    void look(int x, int y) // Finished look
    {
        cout << getName() << " is performing a look...\n";
        int rangeX = pos[0] + x;
        int rangeY = pos[1] + y;
        for (int i = rangeY - 1; i <= rangeY + 1; i++)
        {
            for (int j = rangeX - 1; j <= rangeX + 1; j++)
            {
                if (j < 0 || j >= gameMap->getWidth() || i < 0 || i >= gameMap->getHeight())
                    continue;
                else if (j == rangeX && i == rangeY)
                    continue;
                else
                {
                    gameMap->checkoccupied(j, i);
                    if (gameMap->checkoccupied(j, i))
                    {
                        detect = true;
                        detectPos[0] = j;
                        detectPos[1] = i;
                        cout << "Target spotted at: " << detectPos[0] << "," << detectPos[1] << endl;
                    }
                }
            }
        }
    }
    void stomp(int x, int y) // Finished stomp
    {
        if (detect)
        {
            gameMap->destroyElem(detectPos[0], detectPos[1]);
            gameMap->changecoords(getIndex(), detectPos);
            updateCoords(detectPos);
            resetDetect();
            gameMap->refresh();
        }
        else
        {
            move(x, y);
        }
    }
    void shoot(int x, int y) // Finished shoot
    {
        cout << "Passed in: " << x << ", " << y << endl;
        int shootX = pos[0] + x; // Shoot this positionX
        int shootY = pos[1] + y; // Shoot this positionY
        cout << getName() << " has shot {" << shootX << ", " << shootY << "} " << endl;
            if (gameMap->checkoccupied(shootX, shootY))
            {
                gameMap->destroyElem(shootX, shootY);
                gameMap->refresh();
                cout << getName() << " in position {" << getX() << ", " << getY() << "} has killed {" << shootX << ", " << shootY << "} " << endl;
            }
            else
            {
                cout << getName() << " has missed!\n";
            } 
        return;
    }
    void resetDetect()
    {
        detect = false;
        detectPos[0] = 0;
        detectPos[1] = 0;
    }
    void updateCoords(int arr[])
    {
        pos[0] = arr[0];
        pos[1] = arr[1];
    }
int getRandom(int selection)
{
    int randX, x = 0;
    int limitPosX = gameMap->getWidth() - getX();
    int limitNegX = getX();
    int randY, y = 0;
    int limitPosY = gameMap->getHeight() - getY();
    int limitNegY = getY();
    do {
        // Randomizer X
        randX = rand() % 2;
        if (randX == 0 && limitPosX > 0)
        {
            x = rand() % limitPosX;
        }
        else if (limitNegX > 0)
        {
            x = rand() % limitNegX;
            x = -x;
        }
        // Randomizer Y
        randY = rand() % 2;
        if (randY == 0 && limitPosY > 0)
        {
            y = rand() % limitPosY;
        }
        else if (limitNegY > 0)
        {
            y = rand() % limitNegY;
            y = -y;
        }
    } while (x == 0 && y == 0);
    if (selection == 0)
        return x;
    else if (selection == 1)
        return y;
    else
        return -1;
}
};

class Robocop : public Robot
{
private:
int shootX, shootY;
public:
    Robocop(battlefield *gameMap, string robotName, char robotSymbol, int x, int y, int i)
    {
        name = robotName;
        symbol = robotSymbol;
        this->pos[0] = x;
        this->pos[1] = y;
        this->gameMap = gameMap;
        this->index = i;
    }
    void sequence()
    {
        cout << " --- Sequence: Robocop ---\n";
        move(getX(), getY());
        for (int i = 0; i < 3; i++)
        {
            do {
            shootX = getRandom(0);
            shootY = getRandom(1);
        } while (shootX == 0 && shootY == 0);
        shoot(shootX, shootY);
        }
        return;
    }
};
class Terminator : public Robot
{
public:
    Terminator(battlefield *gameMap, string robotName, char robotSymbol, int x, int y, int i)
    {
        name = robotName;
        symbol = robotSymbol;
        this->pos[0] = x;
        this->pos[1] = y;
        this->gameMap = gameMap;
        this->index = i;
    }
    void sequence()
    {
        cout << " --- Sequence: Terminator ---\n";
        look(getX(), getY());
        stomp(getX(), getY());
        return;
    }
};
class BlueThunder : public Robot
{
private:
    int counter = 0;

public:
    BlueThunder(battlefield *gameMap, string robotName, char robotSymbol, int x, int y, int i)
    {
        name = robotName;
        symbol = robotSymbol;
        this->pos[0] = x;
        this->pos[1] = y;
        this->gameMap = gameMap;
        this->index = i;
    }
    void btshoot()
    {
        int x = 0, y = 0;
        int checkX = getX();
        int checkY = getY();
        do {
            switch (counter)
            {
            case 0:
                y = 1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 1:
                x = 1;
                y = 1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 2:
                x = 1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 3:
                x = 1;
                y = -1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 4:
                y = -1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 5:
                x = -1;
                y = -1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 6:
                x = -1;
                checkX += x;
                checkY += y;
                counter++;
                break;
            case 7:
                x = -1;
                y = 1;
                checkX += x;
                checkY += y;
                counter = 0;
                break;
            default:
                break;
            }
            if (checkX < 0 || checkX >= gameMap->getWidth() || checkY < 0 || checkY >= gameMap->getHeight())
            {
                checkX = getX();
                checkY = getY();
                x = 0;
                y = 0;
                counter++;
            }
        } while (x == 0 && y == 0);
        shoot(x, y);
    }
    void sequence()
    {
        cout << " --- Sequence: BlueThunder ---\n";
        btshoot();
        return;
    }
};
#endif