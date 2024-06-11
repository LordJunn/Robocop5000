#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h> 

// NOTE: Remove MadBot from the starting robots, might need to reimplement a new way to do changecoords
using namespace std;


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

class battlefield {
protected:
    char* robot_symbol_list; // List of all types of robots
    int** robot_coordinates; // List of all robot's coordinates
	string* robot_name_list; // List of all robot's name
    int robot_list_size; // Size of robot_list
	
    int x_axis; // Width of map
    int y_axis; // Height of map
	
	int target_steps; //Final Step
	int current_step; //current step

    char** map; // 2D array of the map

    string logs; // Logs
    string mapstring; // used to print the map
	
	string starting_robot_type[3] = {"RoboCop","Terminator","BlueThunder"}; //used to know how many initial robots ya want
	char starting_robot_symbol[3] = {'R','T','B'};
	string all_robot_types[7] = {"RoboCop","Terminator","BlueThunder","TerminatorRoboCop","Madbot","RoboTank","UltimateRobot"};
	char all_robot_symbol[7] = {'R','T','B','A','M','E','U'};
	mapper<string,char> starting_robot_symbol_type_map = mapper<string,char>(starting_robot_type,starting_robot_symbol,3);	
	mapper<string,char> all_robot_symbol_type_map = mapper<string,char>(all_robot_types,all_robot_symbol,7);

public:
    battlefield() {
		
	}
	
	void setxy(int x_axis,int y_axis){
		//Set x_axis n y_axis
		this->x_axis = x_axis; 
        this->y_axis = y_axis;
	}
	
    battlefield(int x_axis, int y_axis) {

    }
	
    ~battlefield() {
		//Deconstruct
        for (int i = 0; i < x_axis; ++i) {
            delete[] map[i];
        }
        delete[] map;

        for (int i = 0; i < robot_list_size; ++i) {
            delete[] robot_coordinates[i];
        }
        delete[] robot_coordinates;
    }
	
	void initialize_map(){
	    // Allocate memory for the map
        map = new char*[x_axis];
        for (int i = 0; i < x_axis; ++i) {
            map[i] = new char[y_axis];
        }

        //

        // Initialize map with empty spaces
        for (int i = 0; i < x_axis; ++i) {
            for (int j = 0; j < y_axis; ++j) {
                map[i][j] = ' ';
            }
		}
	}
	
	void initialize_size_n_coords(int robot_list_size){
		this->robot_list_size = robot_list_size;
			
		robot_coordinates = new int*[robot_list_size];
		for (int i = 0; i < robot_list_size; ++i) {
			robot_coordinates[i] = new int[2];
		}
	}

	void manualcreate(){
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
	
	int max_robot_limit = (x_axis*y_axis)/9;
	if (max_robot_limit == 0){
		max_robot_limit = 1;
	}
	
	char temp_robot_symbol_list[max_robot_limit] = {};
	
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
				if (temp_robot_symbol_list[j] == '\0'){
					temp_robot_symbol_list[j] = starting_robot_symbol_type_map.get(starting_robot_type[i]);
					break;
				}
			}
		}
		if (total_robot_count == max_robot_limit){
			break;
		}
	}
	// Count array length without '' empty char
	int count = 0;
	
	for (char each:temp_robot_symbol_list){
		if (each != '\0'){
			count+=1;
		}
	}

	robot_symbol_list = new char[count];
	for (int x = 0; x < count ; x++){
		robot_symbol_list[x] = temp_robot_symbol_list[x];
	}
	initialize_map();
	initialize_size_n_coords(count);
	randomize(robot_symbol_list);
	setup();
	
	}
	
	//from file
	void accessfile() {
		string filename;
	
		do {
			cout << "Enter filename: ";
			cin >> filename;

			if (!filename.empty()) {
				ifstream file(filename);
				if (file.good()) {
					cout << "Successful file opening!" << endl;
					// You can proceed with opening and reading the file here
				} else {
					cout << "File does not exist or cannot be opened." << endl;
					// Handle the case where the file doesn't exist or can't be opened
				}
			} else {
				cout << "Invalid filename. Please try again." << endl;
			}
		} while (filename.empty() || !ifstream(filename).good());
		
		ifstream file(filename);

		string line;
		
		// Read and process the "M by N : " line
		getline(file, line);
		istringstream iss(line);
		//this is how to extract stuff from string
		string ignore; 
		//actually its also a variable but we put ignore as var_name so its clear
		iss >> ignore >>ignore >>ignore >>ignore >> x_axis >> y_axis;
		//first instance is stored into ignore.. then second yadayada
		
		// Read and process the "steps: " line
		getline(file, line);
		iss.clear();
		iss.str(line);
		iss >> ignore >> target_steps;

		// Read and process the "robots:" line
		getline(file, line);
		iss.clear();
		iss.str(line);
		iss >> ignore >> robot_list_size;

		// Output the read values for verification
		cout << "x_axis: " << x_axis << " and y_axis: " << y_axis << endl;
		cout << "steps: " << target_steps << endl;
		cout << "robot_list_size: " << robot_list_size << endl;
		
		
		this->robot_symbol_list = new char[robot_list_size];
		this -> robot_name_list = new string[robot_list_size];
		initialize_map();
		initialize_size_n_coords(robot_list_size);
		// Read each robot data
		
		string elem, name, x, y;
		for (int i = 0; i < robot_list_size; ++i) {
			getline(file, line);
			istringstream iss(line);

			iss >> elem >> name >> x >> y;

			cout << "Robot " << i + 1 << ": " << elem << " " << name << " (" << x << ", " << y << ")" << endl;
			
			// Process coordinates
			if (x == "random" || y == "random") {
				x = "-1";
				y = "-1";
			}
			
			robot_symbol_list[i] = all_robot_symbol_type_map.get(elem);
			robot_name_list[i] = name;
			robot_coordinates[i][0] = stoi(x);
			robot_coordinates[i][1] = stoi(y);
			cout << robot_symbol_list[i] << endl;
			
		}
		//settle the -1,-1 randomness part tmr me thank you!!!
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MM!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MM!!!!!!!!!!111
		
		
		setup();
	}

    // Randomly places elements on the battlefield, ensuring no duplicate coordinates
    void randomize(char* robot_symbol_list) {
	
        this->robot_symbol_list = robot_symbol_list;

        // Initialize random engine and distribution
        srand(time(0));
		
        for (int i = 0; i < robot_list_size; ++i) {
            int temp1, temp2;
            bool unique;
            do {
                unique = true; // Assuming every coord is unique at the start
                temp1 = rand()% x_axis;
                temp2 = rand()% y_axis;

                // Check if the generated coordinates are already in use
                for (int j = 0; j < i; ++j) {
                    if (robot_coordinates[j][0] == temp1 && robot_coordinates[j][1] == temp2) {
                        unique = false;
                        break;
                    }
                }
            } while (!unique);

            robot_coordinates[i][0] = temp1;
            robot_coordinates[i][1] = temp2;
        }
    }
	
    // Initializes the battlefield map
    void setup() {
		cout << "e";
        // Give the map initial data
        for (int i = 0; i < x_axis; ++i) {
            for (int j = 0; j < y_axis; ++j) {
                map[i][j] = ' ';
            }
        }
		cout << "r";
		cout << robot_list_size;
        // Place elements on the map
        for (int i = 0; i < robot_list_size; ++i) {
			cout << i << endl;
			cout << endl << robot_symbol_list[i] <<endl;
			cout << "1";
            int x = robot_coordinates[i][0];
			cout << "2";
            int y = y_axis - robot_coordinates[i][1] -1;
			cout << "3";
            map[x][y] = robot_symbol_list[i];
			cout << "4";
        }
		cout << "d";
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
        for (int i = 0; i < robot_list_size; ++i) {
            int x = robot_coordinates[i][0];
            int y = y_axis - robot_coordinates[i][1] -1;
            map[x][y] = robot_symbol_list[i];
        }
    }


    // Changes the coordinates of an element and refreshes the map
    void changecoords(int index, int* new_coords) {
        robot_coordinates[index][0] = new_coords[0];
        robot_coordinates[index][1] = new_coords[1];
        refresh();
    }

    // Prints the coordinates of a specific element
    void printcoords(int index) {
        cout << "Element " << robot_symbol_list[index] << " is at {" << robot_coordinates[index][0] << ", " << robot_coordinates[index][1] << "}" << endl;
    }

    bool checkoccupied(int x, int y){
        if (map[x][y] != ' '){
            return true;
        } else {
            return false;
        }
    }
	
    // Prints the coordinates of all elements
    void logallelem() {
        for (int i = 0; i < robot_list_size; i++) {
            logs += "Element ";
            logs += robot_symbol_list[i];
            logs += " is at {";
            logs += to_string(robot_coordinates[i][0]);
            logs += ", ";
            logs += to_string(robot_coordinates[i][1]);
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
        gameMap = game;
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

	int coords[2]; int gc = 0; int buttonpressed = 0;
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