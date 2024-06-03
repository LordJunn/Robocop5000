#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>


using namespace std;

auto set_random_coordinate(int x_axis, int y_axis, int elem_pos){ //Shouldn't be that hard to understand? the map thing is a map thing for better data management
	
} 

class battlefield {
	private:
		char* elem_list;
		int** coordinates; //coordinates is a 2d [x][2] array
		int elem_list_size;
		int x_axis;
		int y_axis;
		char** map;
		string mapstring;
	public:
		battlefield(){};
		battlefield(int x_axis,int y_axis){
			this->x_axis = x_axis;
			this->y_axis = y_axis;
		}
		void randomize(char* elem_list, int elem_list_size){
			bool run = 1;
			this->elem_list_size = elem_list_size;
			coordinates = new int*[elem_list_size];
			for (int i = 0; i < elem_list_size; ++i) {
				coordinates[i] = new int[2];
			}
			this->elem_list = elem_list;
			for (int x = 0;x < elem_list_size;x++){
				int temp1,temp2;
				temp1 = rand()%x_axis;
				temp2 = rand()%y_axis;
				while (run){
					run = 0;
					for (int y = 0;y < elem_list_size;y++){
						if (temp1 == coordinates[y][0] and temp2 == coordinates[y][1]){
							temp1 = rand()%x_axis;
							temp2 = rand()%y_axis;
						} 
					}
					for (int y = 0;y < elem_list_size;y++){
						if (temp1 == coordinates[y][0] and temp2 == coordinates[y][1]){
							run = 1;
						} 
					}
				}
				coordinates[x][0] = temp1;
				coordinates[x][1] = temp2;
			}				
		}
		
		void setup(){
			map = new char*[x_axis];
			for (int x = 0;x < x_axis;x++){
				map[x]= new char[2];
			}
			for (int x= 0;x < x_axis;x++){
				for (int y= 0; y < y_axis; y++){
					map[x][y] = ' ';
				}
			}
			for (int x = 0; x < elem_list_size;x++){
				map[coordinates[x][0]][coordinates[x][1]] = elem_list[x]; 
			}  
		}
		
		void printmap(){
			mapstring += "+" ;
			for (int x= 0;x < x_axis;x++){
				mapstring+= "---+" ;
			}	
			mapstring += " \n";
			for (int y= 0; y < y_axis; y++){
				for (int x= 0; x<x_axis; x++){
					mapstring += "| " ;
					mapstring += map[x][y] ;
					mapstring +=" ";
					
				}
				mapstring += "|";
				mapstring += " \n";
				for (int x= 0; x<x_axis; x++){
					mapstring+= "+---";
				}		
				mapstring += "+";
				mapstring += " \n";
			}
			cout << mapstring << endl;
		}
			
};
		
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
	int x_axis, y_axis, temp,count;
	bool escape;
	int max_robot_limit;
	string starting_robot_type[4] = {"Robocop","Terminator","BlueThunder","Madbot"}; //evolved robo type dont think need to use
	char robot_symbol[4] = {'R','T','B','M'};
	mapper starting_robot_symbols = mapper(starting_robot_type,robot_symbol,4);
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
	max_robot_limit = (x_axis*y_axis)/9;
	if (max_robot_limit == 0){
		max_robot_limit = 1;
	}
	char elem_list[max_robot_limit] = {};
	//----------------------Objects Selector--------------------------------
	cout << "Initializing map..." << endl;
	cout << "You have selected a " <<x_axis<<" x " << y_axis <<" map" <<endl;
	cout << "Select troops to march on an epic battle! Due to your battlefield size, you are limited to " << max_robot_limit <<" robots." << endl;
	int total_robot_count =0, this_robot_count = 0;
	for (int i = 0; i < 4; i++){ 
		cout << "How many " << starting_robot_type[i] << "?" << endl;
		cin >> this_robot_count;
        total_robot_count += this_robot_count;
		if (total_robot_count > max_robot_limit){
			cout << "Too Much Robots!" << endl;
			total_robot_count -= this_robot_count;			
			i--; 
			continue;
		}
		for (int k = 0; k < this_robot_count; k++){
			for (int j=0;j < max_robot_limit;j++){
				if (elem_list[j] == '\0'){
					elem_list[j] = starting_robot_symbols.get(starting_robot_type[i]);
					break;
				}
			}
		}
		for (char each:elem_list){
			cout << each << endl;
		}
	}
	// Count array length without '' empty char
	count = 0;
	for (char each:elem_list){
		if (each != '\0'){
			count+=1;
		}
	}
	
	//----------------------------Game Loop----------------------------------------------
	battlefield game = battlefield(x_axis,y_axis);
	game.randomize(elem_list,count);
	game.setup();
	game.printmap();
	/*while (1){
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
		cout << "Targets: "<< targetx << " " << targety <<endl;*/
		//--------------------------end of the map generator/shower-------------------------------------
		//------------------------Input getter (doesn't need Enter)----------------------------------------
		/*getch(); //This is because getch() will always send two "Stuff" at the time, and the first stuff is always useless (for arrow keys n delete)
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
	}*/
	
}