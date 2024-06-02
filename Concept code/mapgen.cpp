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


template <typename T1, typename T2> 
class mapper {
	private: 
	T1* arrayAptr;
	T2* arrayBptr;
	int Arraysize;
	public:
	mapper(){};
	mapper(T1* arrayA,T2* arrayB, int size){
		arrayAptr = arrayA;
		arrayBptr = arrayB;
		Arraysize = size;
	}
	T2 get(T1 x){
		for (int i = 0; i < Arraysize; i++){
			if (arrayAptr[i] == x){
				return arrayBptr[i];
			}
		}
		throw std::logic_error(string("Array B Key not found")) ;
	}
	T1 get(T2 x){
		for (int i = 0; i < Arraysize; i++){
			if (arrayBptr[i] == x){
				return arrayAptr[i];
			}
		}
		throw std::logic_error(string("Array A Key not found")) ;
	}
};

int main(){
	int x_axis, y_axis, temp;
	bool escape;
	int max_robot_limit
	string starting_robot_type[4] = ["Robocop","Terminator","BlueThunder","Madbot"]; //evolved robo type dont think need to use
	string robot_symbol[4] = ["R","T","B","M"];
	mapper starting_robot_symbols(starting_robot_type,robot_symbol);
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
	int max_robot_limit = (x_axis*y_axis)/9;
	if (max_robot_limit == 0){
		max_robot_limit = 1;
	}
	char elem_list[max_robot_limit] = {};
	//----------------------Objects Selector--------------------------------
	cout << "Initializing map..." << endl;
	cout << "You have selected a " <<x_axis<<" x " << y_axis <<" map" <<endl;
	cout << "Select troops to march on an epic battle! Due to your battlefield size, you are limited to " << max_robot_limit <<" robots." << endl;
	int total_robot_count, this_robot_count;
	for (int i = 0, i < 4, i++){ 
		cout << "How many " << starting_robot_type[i] << "?" << endl;
		cin >> this_robot_count;
        total_robot_count += this_robot_count;
		if (total_robot_count > max_robot_limit){
			cout << "Too Much Robots!" << endl;
			continue; 
		}
		for (int k = 0; k < this_robot_count; k++){
			for (int j=0;j < max_robot_limit;j++){
				if (elem_list[j] = ""){
					elem_list[j] = starting_robot_symbols.get(starting_robot_type[i])
					
				}
				
			}
		}
	}
	// make a list of all robots + a for loop so you dont need to write all every line
	//Example:{'R','X','X','X','X',' '} means battle field has 1 R and 4 X , we can see there's no obstacles since there's nothing after ' '
	//Example:{'R','X','X',' ','T','T'} means battlefield have 1 R and 2 X's while there's 2 obstacle T's 
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
	while (1){
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