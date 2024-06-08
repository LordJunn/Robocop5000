#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>

// NOTE: Remove MadBot from the starting robots, might need to reimplement a new way to do changecoords
using namespace std;

// Placeholder function for setting random coordinates
auto set_random_coordinate(int x_axis, int y_axis, int elem_pos){ 

} 

class battlefield { 
	private:
		char* elem_list; //exmp: {'R','T'}
		int** coordinates; //exmp:{{2,6},{1,5}}
		
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

		// Randomly places elements on the battlefield, ensuring no duplicate coordinates
		void randomize(char* elem_list, int elem_list_size){// - 
			bool run = 1;
			this->elem_list_size = elem_list_size;
			coordinates = new int*[elem_list_size];
			for (int i = 0; i < elem_list_size; ++i) {
				coordinates[i] = new int[2];
			}
			this->elem_list = elem_list;
			for (int i = 0; i < elem_list_size; ++i) {
				int temp1, temp2;
				bool unique;
				do {
					unique = true; //assuming every coord is unique at the start
					temp1 = rand() % x_axis;
					temp2 = rand() % y_axis;

					// Check if the generated coordinates are already in use
					for (int j = 0; j < i; ++j) {
						if (coordinates[j][0] == temp1 && coordinates[j][1] == temp2) {
							unique = false;
							break; 
							//breaks from this loop to prevent redundant checking
						}
					}
				} while (!unique);

				coordinates[i][0] = temp1;
				coordinates[i][1] = temp2;
			}			
		}
		
		// Initializes the battlefield map
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
				cout << y_axis-(coordinates[x][1]-1) <<endl;
				cout << coordinates[x][0]<< endl;
				cout << "This" << x_axis-(coordinates[x][0])-2 << endl;
				map[coordinates[x][0]][(y_axis-1)-coordinates[x][1]] = elem_list[x]; 
			}  
		}
		
		// Clears the map and refreshes the elements
		void refresh(){
			for (int x= 0;x < x_axis;x++){
				for (int y= 0; y < y_axis; y++){
					map[x][y] = ' ';
				}
			}
			for (int x = 0; x < elem_list_size;x++){
				map[coordinates[x][0]][(y_axis-1)-coordinates[x][1]] = elem_list[x];  
			}  
		}
		
		// Changes the coordinates of an element and refreshes the map
		void changecoords(int x, int* y){
			coordinates[x][0] = y[0];
			coordinates[x][1] = y[1];
			refresh();
		}
		
		// Prints the coordinates of a specific element
		void printcoords(int x){
			cout << "Element "<< elem_list[x] << " is at {" << coordinates[x][0] << "," << coordinates[x][1] << "}" << endl;
		}
		
		// Prints the coordinates of all elements
		void listallelem(){
			for (int x = 0; x < elem_list_size; x++){
				cout << "Element "<< elem_list[x] << " is at {" << coordinates[x][0] << "," << coordinates[x][1] << "}" << endl;
			}
		}
		
		// Prints the battlefield map
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
			mapstring = "";
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

// Here starts robot
class Robot {
private:
	battlefield* gameMap;
    string name;
    char symbol;
    int x, y;
	int lives = 3;
	int kills = 0;
public:
    Robot(string robotName, char robotSymbol) {
        name = robotName;
        symbol = robotSymbol;
    }
    string getName() const {
        return name;
    }
	char getSymbol() const {
        return symbol;
    }
    int getx() const {
    return x;
	}
	int gety() const {
    return y;
    }
	int getLives() const {
        return lives;
    }
	void changecoords(){
		//idk how to change coordinates
	}
};

class RobotMove : public Robot{
	public:
};
class RobotLook : public Robot{
	public:
};
class RobotStomp : public Robot{
	public:
};
class RobotShoot : public Robot{
	public:
};
class Robocop : public Robot, RobotLook, RobotMove, RobotShoot{
	public:
};
class Terminator : public Robot, RobotLook, RobotMove, RobotStomp {
    public:
};
class BlueThunder : public Robot, RobotShoot{
    public:
};

int main(){
	int x_axis, y_axis, temp,count;
	bool escape;
	int max_robot_limit;
	string starting_robot_type[4] = {"Robocop","Terminator","BlueThunder","Madbot"}; //evolved robo type dont think need to use
	char robot_symbol[4] = {'R','T','B','M'};
	mapper starting_robot_symbols = mapper(starting_robot_type,robot_symbol,3);
	string map;
	// ----------------------Map Axis Getter + set all array to empty-----------------------------------
	cout << "Enter x-axis (suggest >5 and <30): " ;
	cin >> x_axis;
	cout << "Enter y-axis (suggest >5 and <13): "; 
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
	}
	// Count array length without '' empty char
	count = 0;
	for (char each:elem_list){
		if (each != '\0'){
			count+=1;
		}
	}
	
	//----------------------------Game Loop----------------------------------------------

	int coords[2]; int gc = 0; int buttonpressed = 0;
	battlefield game = battlefield(x_axis,y_axis);
	game.randomize(elem_list,count);
	game.setup();
	while(1){
		gc++;
		system("cls");
		if (gc == 1){ //testing stuffs
			coords[0] = 0;
			coords[1] = 0;
			game.changecoords(0,coords);
		}
		if (gc == 3){
			coords[0] = 3;
			coords[1] = 4;
			game.changecoords(1,coords);
		}
		game.printmap();
		game.listallelem();
		cout << "Turn " << gc;
		int buttonpressed = getch();
		if (buttonpressed == 0 || buttonpressed == 224)	{
			getch();
		}else if (buttonpressed == 27){
			break;
		}
	}	
}