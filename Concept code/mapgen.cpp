#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

class battlefield
{
private:
    char *elem_list;    // List of all types of robots
    int **coordinates;  // List of all robot's coordinates
    int elem_list_size; // Size of elem_list
    char **map;         // 2D array of the map
    string mapstring;   // used to print the map

protected:
    string logs; // Logs
    int x_axis;  // Width of map
    int y_axis;  // Height of map

public:
    battlefield() {} // Default constructor

    battlefield(int x_axis, int y_axis, int elem_list_size)
    {
        // Set x_axis n y_axis
        this->x_axis = x_axis;
        this->y_axis = y_axis;

        // Allocate memory for the map
        map = new char *[x_axis];
        for (int i = 0; i < x_axis; ++i)
        {
            map[i] = new char[y_axis];
        }

        //

        // Initialize map with empty spaces
        for (int i = 0; i < x_axis; ++i)
        {
            for (int j = 0; j < y_axis; ++j)
            {
                map[i][j] = ' ';
            }
        }

        this->elem_list_size = elem_list_size;

        coordinates = new int *[elem_list_size];
        for (int i = 0; i < elem_list_size; ++i)
        {
            coordinates[i] = new int[2];
        }
    }

    ~battlefield()
    {
        // Deconstruct
        for (int i = 0; i < x_axis; ++i)
        {
            delete[] map[i];
        }
        delete[] map;

        for (int i = 0; i < elem_list_size; ++i)
        {
            delete[] coordinates[i];
        }
        delete[] coordinates;
    }

    // Randomly places elements on the battlefield, ensuring no duplicate coordinates
    void randomize(char *elem_list)
    {

        this->elem_list = elem_list;

        // Initialize random engine and distribution
        srand(time(0));

        for (int i = 0; i < elem_list_size; ++i)
        {
            int temp1, temp2;
            bool unique;
            do
            {
                unique = true; // Assuming every coord is unique at the start
                temp1 = rand() % x_axis;
                temp2 = rand() % y_axis;

                // Check if the generated coordinates are already in use
                for (int j = 0; j < i; ++j)
                {
                    if (coordinates[j][0] == temp1 && coordinates[j][1] == temp2)
                    {
                        unique = false;
                        break;
                    }
                }
            } while (!unique);

            coordinates[i][0] = temp1;
            coordinates[i][1] = temp2;
        }
    }

    // Initializes the battlefield map
    void setup()
    {
        // Clear the map
        for (int i = 0; i < x_axis; ++i)
        {
            for (int j = 0; j < y_axis; ++j)
            {
                map[i][j] = ' ';
            }
        }

        // Place elements on the map
        for (int i = 0; i < elem_list_size; ++i)
        {
            if (coordinates[i][0] != -99 && coordinates[i][1] != -99)
            {
                int x = coordinates[i][0];
                int y = y_axis - coordinates[i][1] - 1;
                map[x][y] = elem_list[i];
            }
        }
    }

    // Clears the map and refreshes the elements
    void refresh()
    {
        // Clear the map
        for (int i = 0; i < x_axis; ++i)
        {
            for (int j = 0; j < y_axis; ++j)
            {
                map[i][j] = ' ';
            }
        }

        // Place elements on the map
        for (int i = 0; i < elem_list_size; ++i)
        {
            if (coordinates[i][0] != -99 && coordinates[i][1] != -99)
            {
                int x = coordinates[i][0];
                int y = y_axis - coordinates[i][1] - 1;
                map[x][y] = elem_list[i];
            }
        }
    }

    // Changes the coordinates of an element and refreshes the map (coords stored inside battlefield)
    void changecoords(int index, int *newcoords)
    {
        coordinates[index][0] = newcoords[0];
        coordinates[index][1] = newcoords[1];
        refresh();
    }

    // Prints the coordinates of a specific element
    void printcoords(int index)
    {
        cout << "Element " << elem_list[index] << " is at {" << coordinates[index][0] << ", " << coordinates[index][1] << "}" << endl;
    }

    bool checkoccupied(int x, int y)
    {
        if (map[x][y_axis - y - 1] != ' ')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Prints the coordinates of all elements
    void logallelem()
    {
        for (int i = 0; i < elem_list_size; i++)
        {
            logs += "Element ";
            logs += elem_list[i];
            logs += " is at {";
            logs += to_string(coordinates[i][0]);
            logs += ", ";
            logs += to_string(coordinates[i][1]);
            logs += "}\n";
        }
    }

    void printlogs()
    {
        cout << logs;
        logs = "";
    }

    // Prints the battlefield map
    void printmap()
    {
        mapstring += "+";
        for (int i = 0; i < x_axis; i++)
        {
            mapstring += "---+";
        }
        mapstring += "\n";
        for (int i = 0; i < y_axis; i++)
        {
            for (int j = 0; j < x_axis; j++)
            {
                mapstring += "| ";
                mapstring += map[j][i];
                mapstring += " ";
            }
            mapstring += "|\n";
            for (int j = 0; j < x_axis; j++)
            {
                mapstring += "+---";
            }
            mapstring += "+\n";
        }
        cout << mapstring << endl;
        mapstring = "";
    }

    void destroyElem(int x, int y)
    {
        int index = findIndex(x, y);
        if (index != -1)
        {
            elem_list[index] = ' ';
            coordinates[index][0] = -99;
            coordinates[index][1] = -99;
        }
        return;
    }
    int findIndex(int x, int y)
    {
        for (int i = 0; i < elem_list_size; ++i)
        {
            if (coordinates[i][0] == x && coordinates[i][1] == y)
            {
                return i; // Return the row index if the pair (x, y) is found
            }
        }
        return -1;
    }
    // Getters
    int getX(int index)
    {
        return coordinates[index][0];
    }
    int getY(int index)
    {
        return coordinates[index][1];
    }
    int getWidth() const
    {
        return x_axis;
    }
    int getHeight() const
    {
        return y_axis;
    }
};

template <typename T1, typename T2>
class mapper
{
private:
    T1 *arrayAptr;
    T2 *arrayBptr;
    int Arraysize;

public:
    mapper(){};
    mapper(T1 *arrayA, T2 *arrayB, int size)
    {
        arrayAptr = arrayA;
        arrayBptr = arrayB;
        Arraysize = size;
    }
    T2 get(T1 x)
    {
        for (int i = 0; i < Arraysize; i++)
        {
            if (arrayAptr[i] == x)
            {
                return arrayBptr[i];
            }
        }
        throw std::logic_error(string("Array B Key not found"));
    }
    T1 get(T2 x)
    {
        for (int i = 0; i < Arraysize; i++)
        {
            if (arrayBptr[i] == x)
            {
                return arrayAptr[i];
            }
        }
        throw std::logic_error(string("Array A Key not found"));
    }
};

// Here starts robot
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

int main()
{
    int x_axis, y_axis, temp, count;
    bool escape;
    int max_robot_limit;
    string starting_robot_type[3] = {"Robocop", "Terminator", "BlueThunder"}; // used to know how many initial robots ya want
    char starting_robot_symbol[3] = {'R', 'T', 'B'};
    string all_robot_types[7] = {"Robocop", "Terminator", "BlueThunder", "TerminatorRoboCop", "MadBot", "Robotank", "UltimateRobot"};
    char all_robot_symbol[7] = {'R', 'T', 'B', 'A', 'M', 'E', 'U'};
    mapper starting_robot_symbols = mapper(starting_robot_type, starting_robot_symbol, 3);
    string map;
    // ----------------------Map Axis Getter + set all array to empty-----------------------------------
    // get x_axis
    do
    {
        cout << "Enter x-axis (>3 and <30): ";
        cin >> x_axis;
        if (x_axis <= 3 or x_axis >= 30)
        {
            cout << "invalid number!" << endl;
        }
    } while (x_axis <= 3 or x_axis >= 30);

    // get y_axis
    do
    {
        cout << "Enter y-axis (>3 and <13): ";
        cin >> y_axis;
        if (y_axis <= 3 or y_axis >= 13)
        {
            cout << "invalid number!" << endl;
        }
    } while (y_axis <= 3 or y_axis >= 13);

    max_robot_limit = (x_axis * y_axis) / 9;
    if (max_robot_limit == 0)
    {
        max_robot_limit = 1;
    }
    char elem_list[max_robot_limit] = {};

    //----------------------Objects Selector--------------------------------
    cout << "Initializing map..." << endl;
    cout << "You have selected a " << x_axis << " x " << y_axis << " map" << endl;
    cout << "Select troops to march on an epic battle! Due to your battlefield size, you are limited to " << max_robot_limit << " robots." << endl;
    int total_robot_count = 0, this_robot_count = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "How many " << starting_robot_type[i] << "?" << endl;
        cin >> this_robot_count;
        total_robot_count += this_robot_count;
        if (total_robot_count > max_robot_limit)
        {
            cout << "Too Much Robots!" << endl;
            total_robot_count -= this_robot_count;
            i--;
            continue;
        }
        for (int k = 0; k < this_robot_count; k++)
        {
            for (int j = 0; j < max_robot_limit; j++)
            {
                if (elem_list[j] == '\0')
                {
                    elem_list[j] = starting_robot_symbols.get(starting_robot_type[i]);
                    break;
                }
            }
        }
        if (total_robot_count == max_robot_limit)
        {
            break;
        }
    }

    //----------------------------Game Loop----------------------------------------------
    int gc = 0;
    int buttonpressed = 0;
    int *test;
    // counting length of elem_list to initialize battlefield
    count = 0; // Count for instantiating robots
    for (char each : elem_list)
    {
        if (each != '\0')
        {
            count += 1;
        }
    }
    battlefield game = battlefield(x_axis, y_axis, count);
    game.randomize(elem_list);
    game.setup();
    Robot *robot_list[count] = {}; // Array for instantiated robots
    for (int i = 0; i < count; i++)
    {
        if (elem_list[i] == 'R')
        {
            robot_list[i] = new Robocop(&game, "Robocop", 'R', game.getX(i), game.getY(i), i);
        }
        else if (elem_list[i] == 'T')
        {
            robot_list[i] = new Terminator(&game, "Terminator", 'T', game.getX(i), game.getY(i), i);
        }
        else if (elem_list[i] == 'B')
        {
            robot_list[i] = new BlueThunder(&game, "BlueThunder", 'B', game.getX(i), game.getY(i), i);
        }
    }
    cout << "Finished instantiating robots!\n";
    while (1)
    {
        gc++;
        cout << endl
             << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << "Turn " << gc << endl
             << endl;
        game.printmap();
        game.logallelem();
        game.printlogs();
        game.printcoords(4);
        // Testing stuff
        for (int i = 0; i < count; i++)
        {
            if (robot_list[i]->getSymbol() == 'R')
            {
                robot_list[i]->sequence();
            }
            else if (robot_list[i]->getSymbol() == 'T')
            {
                robot_list[i]->sequence();
            }
            else if (robot_list[i]->getSymbol() == 'B')
            {
                robot_list[i]->sequence();
            }
        }
        // Testing end
        int buttonpressed = getch();
        if (buttonpressed == 0 || buttonpressed == 224)
        {
            getch();
        }
        else if (buttonpressed == 27)
        {
            break;
        }
    }
    return 0;
}