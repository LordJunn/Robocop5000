#include <iostream>
#include "battlefield.h"
#include "robot.h"
#include "battlefield.cpp"

using namespace std;

int main()
{
    int x_axis = 7, y_axis = 5, count = 6;

    battlefield game = battlefield(x_axis, y_axis, count);
    cout << game.getHeight() << endl;
}