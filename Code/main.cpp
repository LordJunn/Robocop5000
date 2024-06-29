#include "battlefield.h"
#include "robot.h"
#include "print.h"

#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

ofstream resultfile("result.txt"); //global

void endgame(string name){
	print("GAME ENDED! THE WINNER IS ",name,"!\n");
	resultfile.close();
	exit(0);
}


int main(){
	int option;
	bool temp = 0;
	battlefield game = battlefield();
	int buttonpressed = 0;
	while (!temp){
		temp = 1;
		cout << "Select an Option: \n1) Manual setup\n2) File Setup\n3) Help \n\nOption: ";
		cin >> option;
		if (option == 1){
			game.manualcreate();
		
		} else if (option == 2){
			game.accessfile();
		} else if (option == 3){
			cout << "\n----------------FAQ-----------------\n\nFAQ: Why is the file not running/found?" << endl;
			cout << "ANS: Double check to make sure the file is in the 'Inputs' folder which is in the same location as this program" <<endl << endl;
			
			cout << "FAQ: Why does the file may suddenly crash during program?" << endl;
			cout << "ANS: Make sure the width M is more than 3 and less than 13 and Height N is more than 3 and less than 30\n\n\n----------------END-----------------\n\nPress Enter to continue...\n\n" <<endl;
			temp = 0;
			cin.clear();
			cin.ignore(10000,'\n');
			buttonpressed = getch();
			if (buttonpressed == 0 || buttonpressed == 224)
			{
				getch();
			}
			else if (buttonpressed == 27)
			{}
			
		} else {
			temp = 0;
			cin.clear();
			cin.ignore(10000,'\n');
		}
	}

    //----------------------------Game Loop----------------------------------------------
    int gc = 0;
	int robotsleft = game.get_elem_list_size();
	
    // counting length of elem_list to initialize battlefield
    int count = 0; // Count for instantiating robots
	
    Robot* robot_list[game.get_elem_list_size()] = {}; // Array for instantiated robots
    for (int i = 0; i < game.get_elem_list_size(); i++)
    {	
			if (game.elem_list[i] == 'R')
			{
				robot_list[i] = new Robocop(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'T')
			{	
				robot_list[i] = new Terminator(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'B')
			{
				robot_list[i] = new BlueThunder(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'A')
			{	
				robot_list[i] = new TerminatorRoboCop(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'M')
			{
				robot_list[i] = new Madbot(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'E')
			{	
				robot_list[i] = new RoboTank(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			}
			else if (game.elem_list[i] == 'U')
			{
				robot_list[i] = new UltimateRobot(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			} 
			else if (game.elem_list[i] == 'X')
			{
				robot_list[i] = new ExplodoBot(&game, game.get_name(i), game.getX(i), game.getY(i), i);
			}
    }
    print("Finished instantiating robots!\n\nOriginal Presets: \n");
	game.printmap();
    game.logallelem();
	game.printlogs();
    while (1)
    {
        gc++;
		if (gc >= game.get_steps()){
			print("Game Finished. Max Steps Reached!");
			resultfile.close();
			exit(0);
		}
        print("\n\n");
        print("--------------------------------------------------------------------------------------------\n");
        print("Turn ");
		print(gc);
		print("\n\n");
		
		for (int i = 0; i < game.get_elem_list_size(); i++){
			if (game.checkrevive(i) == 1){
				game.revive(i);
				if (game.checklives(i) == 0){
					robotsleft -= 1;
				}
				if (game.checklives(i) != 0){
					print(game.elem_list[i]," is revived at ",game.getX(i),",",game.getY(i),"!\n");
					print("Lives left: ",game.checklives(i),"\n\n");
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
				print("BAD ENDING! No Robots left....\n");
				resultfile.close();
				exit(0);
			}
		}
		robotsleft = game.get_elem_list_size();

		
        for (int i = 0; i < game.get_elem_list_size(); i++)
        {	
			string newname;
			if (game.checkrevive(i) == 0){
				robot_list[i]->operate();
				print("\n");
				if (robot_list[i]->checkkills() >= 3){
					print(robot_list[i]->showname()) ;

					if (game.elem_list[i] == 'R'||game.elem_list[i] == 'T'){
						game.change_elem_list(i,'A');
						newname = "TerminatorRoboCop";
						if (game.check_custom() == 1){
							robot_list[i] = new TerminatorRoboCop(&game, game.get_name(i), game.getX(i), game.getY(i), i);
						} else {
							robot_list[i] = new TerminatorRoboCop(&game, "TerminatorRoboCop", game.getX(i), game.getY(i), i);
						}
					} else if (game.elem_list[i] == 'A'||game.elem_list[i] == 'E'||game.elem_list[i] == 'X'){
						game.change_elem_list(i,'U');
						newname = "UltimateRobot";
						if (game.check_custom() == 1){
							robot_list[i] = new UltimateRobot(&game, game.get_name(i), game.getX(i), game.getY(i), i);
						} else {
							robot_list[i] = new UltimateRobot(&game, "UltimateRobot", game.getX(i), game.getY(i), i);	
						}				
					} else if (game.elem_list[i] == 'B'){
						game.change_elem_list(i,'M');
						newname = "Madbot";
						if (game.check_custom() == 1){
							robot_list[i] = new Madbot(&game, game.get_name(i), game.getX(i), game.getY(i), i);
						} else {
							robot_list[i] = new Madbot(&game, "Madbot", game.getX(i), game.getY(i), i);		
						}						
					} else if (game.elem_list[i] == 'M'){
						game.change_elem_list(i,'E');
						newname = "RoboTank";
						if (game.check_custom() == 1){
							robot_list[i] = new RoboTank(&game, game.get_name(i), game.getX(i), game.getY(i), i);
						} else {
							robot_list[i] = robot_list[i] = new RoboTank(&game, "RoboTank", game.getX(i), game.getY(i), i);		
						}							
					}
					print(" has become ",newname,"\n");
				}
			}
        }
        // Testing end
        game.printmap();
        game.logallelem();
        game.printlogs();
        buttonpressed = getch();
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