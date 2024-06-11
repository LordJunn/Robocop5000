#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h> 

// NOTE: Remove MadBot from the starting robots, might need to reimplement a new way to do changecoords
using namespace std;

class battlefield {
private:
    char* elem_list; // Example: {'R', 'T'}
    int** coordinates; // Example: {{2, 6}, {1, 5}}
    int elem_list_size;
    int x_axis;
    int y_axis;
    char** map;

    string logs;
    string mapstring;

public:
    battlefield() {}

    battlefield(int x_axis, int y_axis) {
        //Set x_axis n y_axis
		this->x_axis = x_axis; 
        this->y_axis = y_axis;

        // Allocate memory for the map
        map = new char*[x_axis];
        for (int i = 0; i < x_axis; ++i) {
            map[i] = new char[y_axis];
        }

        // Initialize map with empty spaces
        for (int i = 0; i < x_axis; ++i) {
            for (int j = 0; j < y_axis; ++j) {
                map[i][j] = ' ';
            }
        }
    }

    ~battlefield() {
		//Deconstruct
        for (int i = 0; i < x_axis; ++i) {
            delete[] map[i];
        }
        delete[] map;

        for (int i = 0; i < elem_list_size; ++i) {
            delete[] coordinates[i];
        }
        delete[] coordinates;
    }

    // Randomly places elements on the battlefield, ensuring no duplicate coordinates
    void randomize(char* elem_list, int elem_list_size) {
        this->elem_list_size = elem_list_size;
		
		
        coordinates = new int*[elem_list_size];
        for (int i = 0; i < elem_list_size; ++i) {
            coordinates[i] = new int[2];
        }
		
		
        this->elem_list = elem_list;

        // Initialize random engine and distribution
        srand(time(0));
		
        for (int i = 0; i < elem_list_size; ++i) {
            int temp1, temp2;
            bool unique;
            do {
                unique = true; // Assuming every coord is unique at the start
                temp1 = rand()% x_axis;
                temp2 = rand()% y_axis;

                // Check if the generated coordinates are already in use
                for (int j = 0; j < i; ++j) {
                    if (coordinates[j][0] == temp1 && coordinates[j][1] == temp2) {
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
    void setup() {
        // Clear the map
        for (int i = 0; i < x_axis; ++i) {
            for (int j = 0; j < y_axis; ++j) {
                map[i][j] = ' ';
            }
        }

        // Place elements on the map
        for (int i = 0; i < elem_list_size; ++i) {
            int x = coordinates[i][0];
            int y = y_axis - coordinates[i][1] -1;
            map[x][y] = elem_list[i];
        }
    }

    // Clears the map and refreshes the elements
    void refresh() {
        // Clear the map
        for (int i = 0; i < x_axis; ++i) {
            for (int j = 0; j < y_axis; ++j) {
                map[i][j] = ' ';
            }
        }

        // Place elements on the map
        for (int i = 0; i < elem_list_size; ++i) {
            int x = coordinates[i][0];
            int y = y_axis - coordinates[i][1] -1;
            map[x][y] = elem_list[i];
        }
    }


    // Changes the coordinates of an element and refreshes the map
    void changecoords(int index, int* new_coords) {
        coordinates[index][0] = new_coords[0];
        coordinates[index][1] = new_coords[1];
        refresh();
    }

    // Prints the coordinates of a specific element
    void printcoords(int index) {
        cout << "Element " << elem_list[index] << " is at {" << coordinates[index][0] << ", " << coordinates[index][1] << "}" << endl;
    }

    // Prints the coordinates of all elements
    void logallelem() {
        for (int i = 0; i < elem_list_size; i++) {
            logs += "Element ";
            logs += elem_list[i];
            logs += " is at {";
            logs += to_string(coordinates[i][0]);
            logs += ", ";
            logs += to_string(coordinates[i][1]);
            logs += "}\n";
        }
    }

    void printlogs() {
        cout << logs;
        logs = "";
    }

    // Prints the battlefield map
    void printmap() {
        mapstring += "+";
        for (int i = 0; i < x_axis; i++) {
            mapstring += "---+";
        }
        mapstring += "\n";
        for (int i = 0; i < y_axis; i++) {
            for (int j = 0; j < x_axis; j++) {
                mapstring += "| ";
                mapstring += map[j][i];
                mapstring += " ";
            }
            mapstring += "|\n";
            for (int j = 0; j < x_axis; j++) {
                mapstring += "+---";
            }
            mapstring += "+\n";
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

/* Here starts robot
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
};*/

int main(){
	int x_axis, y_axis, temp,count;
	bool escape;
	int max_robot_limit;
	string starting_robot_type[3] = {"Robocop","Terminator","BlueThunder"}; //used to know how many initial robots ya want
	char starting_robot_symbol[3] = {'R','T','B'};
	string all_robot_types[7] = {"Robocop","Terminator","BlueThunder","TerminatorRoboCop","MadBot","Robotank","UltimateRobot"};
	char all_robot_symbol[7] = {'R','T','B','A','M','E','U'};
	mapper starting_robot_symbols = mapper(starting_robot_type,starting_robot_symbol,3);
	string map;
	// ----------------------Map Axis Getter + set all array to empty-----------------------------------
	//get x_axis
	do{
		cout << "Enter x-axis (>3 and <30): " ;
		cin >> x_axis;
		if (x_axis <= 3 or x_axis >= 30){
			cout << "invalid number!" <<endl;
		}
	} while (x_axis <= 3 or x_axis >= 30);
	
	//get y_axis
	do{
	cout << "Enter y-axis (>3 and <13): ";
	cin >> y_axis;
		if (y_axis <= 3 or y_axis >= 13){
			cout << "invalid number!" << endl;
		}
	} while (y_axis <= 3 or y_axis >= 13);
	
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
	for (int i = 0; i < 3; i++){ 
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
		if (total_robot_count == max_robot_limit){
			break;
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
		cout << endl << endl;
		cout << "--------------------------------------------------------------------------------------------" <<endl;
		cout << "Turn " << gc <<endl <<endl;
		game.printmap();
		game.logallelem();
		game.printlogs();
		game.printcoords(4);
		int buttonpressed = getch();
		if (buttonpressed == 0 || buttonpressed == 224)	{
			getch();
		}else if (buttonpressed == 27){
			break;
		}
	}	
}