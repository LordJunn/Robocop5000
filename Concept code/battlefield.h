#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
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
#endif