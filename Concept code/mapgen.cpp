#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

// NOTE: Need to make a getCoords in the game loop thing so that we can instantiate robots with the coordinates.
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
    int getIndex() const
    {
        return index;
    }
    void move(int x, int y) // Finished move
    {
        int oldX = x;
        int oldY = y;
        int newX = x;
        int newY = y;
        int arr[2];
        int moves = rand() % 8;
        switch (moves)
        {
        case 0:
            newY++; // Up
            break;
        case 1:
            newX--; // Left
            break;
        case 2:
            newY--; // Down
            break;
        case 3:
            newX++; // Right
            break;
        case 4:
            newX--; // Up left
            newY++;
            break;
        case 5:
            newX++; // Up right
            newY++;
            break;
        case 6:
            newX--; // Down left
            newY--;
            break;
        case 7:
            newX++; // Down right
            newY--;
            break;
        }
        cout << "Robot tried to move to " << newX << "," << newY << endl;
        if (newX < 0 || newX >= gameMap->getWidth() || newY < 0 || newY >= gameMap->getHeight())
        {
            newX = oldX;
            newY = oldY;
            cout << "Robot tried to cross the borders, it has wasted a move!\n";
        }
        else if (gameMap->checkoccupied(newX, newY) == true)
        {
            newX = oldX;
            newY = oldY;
            cout << "There seems to be something in the way...\n";
        }
        arr[0] = {newX};
        arr[1] = {newY};
        updateCoords(arr);
        gameMap->changecoords(getIndex(), arr);
    }
    void look(int x, int y) // Finished look
    {
        cout << "Robot is performing a look...\n";
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
                    if (gameMap->checkoccupied(j, i) == true)
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
};

class Robocop : public Robot
{
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
};
class BlueThunder : public Robot
{
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
    // Count array length without '' empty char
    count = 0;
    for (char each : elem_list)
    {
        if (each != '\0')
        {
            count += 1;
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
    Robot robot_list[count] = {}; // Array for instantiated robots
    for (int i = 0; i < count; i++)
    {
        if (elem_list[i] == 'R')
        {
            robot_list[i] = Robocop(&game, "Robocop", 'R', game.getX(i), game.getY(i), i);
        }
        else if (elem_list[i] == 'T')
        {
            robot_list[i] = Terminator(&game, "Terminator", 'T', game.getX(i), game.getY(i), i);
        }
        else if (elem_list[i] == 'B')
        {
            robot_list[i] = BlueThunder(&game, "BlueThunder", 'B', game.getX(i), game.getY(i), i);
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
        // Testing stuff
        robot_list[0].look(0, 0);
        robot_list[0].stomp(robot_list->getX(), robot_list->getY());
        // Testing end
        game.printmap();
        game.logallelem();
        game.printlogs();
        game.printcoords(4);
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
}