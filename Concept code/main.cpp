#include "battlefield.h"
#include "robot.h"

#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

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