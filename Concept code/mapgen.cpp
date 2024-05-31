#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

auto set_random_coordinate(int x_axis, int y_axis, int elem_pos){ //Shouldn't be that hard to understand? the map thing is a map thing for better data management
	
} 

int main(){
	int x_axis, y_axis, temp;
	bool escape;
	bool alwaystrue = true;
	string map;
	// ----------------------Map Axis Getter + set all array to empty-----------------------------------
	cout << "Enter x-axis (suggest >5 and <20): " ;
	cin >> x_axis;
	cout << "Enter y-axis (suggest >5 and <12): "; 
	cin >> y_axis;
	char array[x_axis][y_axis] = {};
	for (int x=  0;x < x_axis;x++){
		for (int y= 0; y< y_axis; y++){
			array[x][y] = ' ';
		}
	}
	//----------------------Objects Selector--------------------------------
	cout << "Initializing map..." << endl;
	cout << "You have selected a " <<x_axis<<" x " << y_axis <<" map" <<endl;
	cout << "Select 
	char elem_list[elem_count+2] = {}; 
	int elem_pos[elem_count+2][2] = {}
	//Example:{'R','X','X',' ','X','X',' '} means you have 1 R and 2 X while opponent has 2 X, we can see its yours or opp's according to the empty char
	//Example:{'R',' ','X','X',' ','T','T'} means you have 1 R, opponent has 2 X's while there's 2 obstacle T's 
	//---------------------- end of Map Axis Getter + set all to empty-----------------------------------
	//------------------------Random robot placing-------------------------------------
/*	int robotR_x_axis, robotR_y_axis;
	robotR_x_axis = rand()%x_axis;
	robotR_y_axis = rand()%y_axis;
	array[robotR_x_axis][robotR_y_axis] = 'R';
	cout << "Robot R is generated at " << robotR_x_axis << " " << robotR_y_axis <<endl << "--Press Enter to continue!--";
	getch(); */
	for (int index; index < temp; index++){
		set_random_coordinate(int x_axis, int y_axis, map<string, int> elem_pos);
	}
	//------------------------end of Random robot placing-------------------------------------
	//-------------------Finding the robots ( currently only R )-----------------------------
	int targetx, targety;
	for (int x=  0;x < x_axis;x++){
		for (int y= 0; y<y_axis; y++){
			if (array[x][y] == 'R'){
				targetx = x;
				targety = y;
			}
		}
	}
	//-------------------end of Finding the robots -----------------------------
	//----------------------------Game Loop----------------------------------------------
	while (alwaystrue){
		//----------------------------map generator/shower-----------------------------------------
		system("CLS");
		map += "+" ;
		for (int z= 0;z < x_axis;z++){
			map+= "---+" ;
		}	
		map += " \n";
		for (int y= 0; y < y_axis; y++){
			for (int x= 0; x<x_axis; x++){
				if (x == targetx && y == targety){
					map += "|[" ;
					map += array[x][y];
					map +="]";
				} else{
					map += "| " ;
					map += array[x][y] ;
					map +=" ";
				}
			}
			map += "|";
			map += " \n";
			for (int x= 0; x<x_axis; x++){
				map+= "+---";
			}		
			map += "+";
			map += " \n";
		}
		cout << map << endl;
		map = "";
		cout << "Targets: "<< targetx << " " << targety <<endl;
		//--------------------------end of the map generator/shower-------------------------------------
		//------------------------Input getter (doesn't need Enter)----------------------------------------
		getch(); //This is because getch() will always send two "Stuff" at the time, and the first stuff is always useless (for arrow keys n delete)
		switch(getch()) { // the real value
			case 72: //left arrow key
				targety -= 1;
				break;
			case 80: //down '' '' 
				targety += 1;
				break;
			case 77: //right '' '' 
				targetx += 1;
				break;
			case 75: //left '' '' 
				targetx -= 1;
				break;
			case 83: //Delete to make sure one can exit the game loop
				escape = true;
				break;
		}
		if (escape == true){
			break;
		}
		//-----------------------------end of input getter-----------------------------------------------------------
	}
	
}