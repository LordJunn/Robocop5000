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

void endgame(string name){
	cout << "GAME ENDED! THE WINNER IS " << name << "!" <<endl;
	exit(0);
}

int main(){
	int option;
	bool temp = 0;
	battlefield game = battlefield();
	while (!temp){
		temp = 1;
		cout << "Select an Option: \n1) Manual setup\n2) Setup through file (requires a txt file with proper format)\n Option: ";
		cin >> option;
		if (option == 1){
			game.manualcreate();
		
		} else if (option == 2){
			game.accessfile();
		} else {
			temp = 0;
			cin.clear();
			cin.ignore(10000,'\n');
		}
	}

    //----------------------------Game Loop----------------------------------------------
    int gc = 0;
    int buttonpressed = 0;
	int robotsleft = game.get_elem_list_size();
	
    // counting length of elem_list to initialize battlefield
    int count = 0; // Count for instantiating robots
	
    Robot* robot_list[game.get_elem_list_size()] = {}; // Array for instantiated robots
    for (int i = 0; i < game.get_elem_list_size(); i++)
    {	
			if (game.elem_list[i] == 'R')
			{
				robot_list[i] = new Robocop(&game, "Robocop", game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'T')
			{	
				robot_list[i] = new Terminator(&game, "Terminator", game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'B')
			{
				robot_list[i] = new BlueThunder(&game, "BlueThunder", game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'A')
			{	
				robot_list[i] = new TerminatorRoboCop(&game, "TerminatorRoboCop", game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'M')
			{
				robot_list[i] = new Madbot(&game, "Madbot", game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'E')
			{	
				robot_list[i] = new RoboTank(&game, "RoboTank", game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'U')
			{
				robot_list[i] = new UltimateRobot(&game, "UltimateRobot", game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'X')
			{
				robot_list[i] = new ExplodoBot(&game, "Explodobot", game.getX(i), game.getY(i), i);
			}
    }
    cout << "Finished instantiating robots!\n\nOriginal Presets: \n";
	game.printmap();
    game.logallelem();
	game.printlogs();
    while (1)
    {
        gc++;
        cout << endl
             << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << "Turn " << gc << endl
             << endl;

		for (int i = 0; i < game.get_elem_list_size(); i++){
			if (game.checkrevive(i) == 1){
				game.revive(i);
				if (game.checklives(i) == 0){
					robotsleft -= 1;
				}
				if (game.checklives(i) != 0){
					cout << game.elem_list[i] << " is revived at " << game.getX(i) << "," << game.getY(i) << "!" << endl;
					cout << "Lives left: " << game.checklives(i) << endl << endl;
					robot_list[i]->refreshpos(game.getX(i),game.getY(i));
				}

			}
		}
		if (robotsleft <= 1){
			if (robotsleft == 1){
				for (int i = 0; i < game.get_elem_list_size(); i++){
					if (game.checklives(i) != 0){
						endgame(game.get_name(i));
					}
				}
			} else {
				cout << "BAD ENDING! No Robots left...." << endl;
				exit(0);
			}
		}
		robotsleft = game.get_elem_list_size();

		
        for (int i = 0; i < game.get_elem_list_size(); i++)
        {	
			if (game.checkrevive(i) == 0){
				robot_list[i]->operate();
				cout << endl;
				if (robot_list[i]->checkkills() >= 3){
					cout << robot_list[i]->showname() ;
					if (game.elem_list[i] == 'R'||game.elem_list[i] == 'T'){
						game.change_elem_list(i,'A');
						robot_list[i] = new TerminatorRoboCop(&game, "TerminatorRoboCop", game.getX(i), game.getY(i), i);
					} else if (game.elem_list[i] == 'A'||game.elem_list[i] == 'E'||game.elem_list[i] == 'X'){
						game.change_elem_list(i,'U');
						robot_list[i] = new UltimateRobot(&game, "UltimateRobot", game.getX(i), game.getY(i), i);						
					} else if (game.elem_list[i] == 'B'){
						game.change_elem_list(i,'M');
						robot_list[i] = new Madbot(&game, "Madbot", game.getX(i), game.getY(i), i);						
					} else if (game.elem_list[i] == 'M'){
						game.change_elem_list(i,'E');
						robot_list[i] = new RoboTank(&game, "RoboTank", game.getX(i), game.getY(i), i);							
					}
					cout << " has become " << robot_list[i]->showname() << endl;
				}
			}
        }
        // Testing end
        game.printmap();
        game.logallelem();
        game.printlogs();
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