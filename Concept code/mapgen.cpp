#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

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
    int** coordinates; // List of all robot's coordinates
	string* elem_name_list; // List of all robot's name
	int elem_lives; 
    int elem_list_size; // Size of robot_list
	
	int* revivecount;
	int* revivequeue;

    int x_axis; // Width of map
    int y_axis; // Height of map
	
	int target_steps; //Final Step
	int current_step; //current step

    char** map; // 2D array of the map

    string logs; // Logs
    string mapstring; // used to print the map
	
	string all_robot_types[7] = {"RoboCop","Terminator","BlueThunder","TerminatorRoboCop","Madbot","RoboTank","UltimateRobot"};
	char all_robot_symbol[7] = {'R','T','B','A','M','E','U'};
	
	mapper<string,char> all_robot_symbol_type_map = mapper<string,char>(all_robot_types,all_robot_symbol,7);

public:
    char* elem_list; // List of all types of robots
	
    battlefield() {
		
	}
	
	void setxy(int x_axis,int y_axis){
		//Set x_axis n y_axis
		this->x_axis = x_axis; 
        this->y_axis = y_axis;
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
	
	void initialize_size_n_coords(int elem_list_size){ //and also revivequeue n revivecount
		this->elem_list_size = elem_list_size;
			
		coordinates = new int*[elem_list_size];
		for (int i = 0; i < elem_list_size; ++i) {
			coordinates[i] = new int[2];
		}
		
		revivecount = new int[elem_list_size];
		for (int i = 0; i < elem_list_size; ++i) {
			revivecount[i] = 3;
		}
		
		revivequeue = new int[elem_list_size];
		for (int i = 0; i < elem_list_size; ++i) {
			revivequeue[i] = 0;  //means no need revive
		}
		
	}

	void manualcreate();
	
	void accessfile();

    // Randomly places elements on the battlefield, ensuring no duplicate coordinates
    void randomize(char* elem_list) {
	
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
        // Give the map initial data
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
			if (checkrevive(i) == 0){
				int x = coordinates[i][0];
				int y = y_axis - coordinates[i][1] -1;
				map[x][y] = elem_list[i];
			}
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

    bool checkoccupied(int x, int y){
        if (map[x][y_axis - y - 1] != ' '){
            return true;
        } else {
            return false;
        }
    }
	
    // Prints the coordinates of all elements
    void logallelem() {
        for (int i = 0; i < elem_list_size; i++) {
            logs += "Element ";
            logs += elem_list[i];
            logs += " is at {";
			if (coordinates[i][0] != -99){
				logs += to_string(coordinates[i][0]);
				logs += ", ";
				logs += to_string(coordinates[i][1]);
			} else {
				logs += "HEAVEN";
			}
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

    void destroyElem(int x, int y){ //reduce tanks hp and remove em completely
        int index = findIndex(x, y);
		revivecount[index] -= 1;
		revivequeue[index] = 1;
		coordinates[index][0] = -99;
		coordinates[index][1] = -99;
    }
	
    int findIndex(int x, int y){
        for (int i = 0; i < elem_list_size; ++i)
        {
            if (coordinates[i][0] == x && coordinates[i][1] == y)
            {
                return i; // Return the row index if the pair (x, y) is found
            }
        }
        return -1;
    }
    // Getters
    int getX(int index){
        return coordinates[index][0];
    }
	
    int getY(int index){
        return coordinates[index][1];
    }
	
    int getWidth() const{
        return x_axis;
    }
	
    int getHeight() const {
        return y_axis;
    }
	
	int get_elem_list_size(){
		return elem_list_size;
	}
	
	bool checkrevive(int x){
		if (revivequeue[x] == 1){
			return true;
		} 
		return false;
	}
	
	int checklives(int x){
		return revivecount[x];
	}
	
	void revive(int x){
		if (revivecount[x] > 0){
			revivequeue[x] = 0;
			int temp1, temp2;
			bool unique;
			do {
				unique = true; // Assuming every coord is unique at the start
				temp1 = rand()% x_axis;
				temp2 = rand()% y_axis;

				// Check if the generated coordinates are already in use
				for (int j = 0; j < elem_list_size; ++j) {
					if (coordinates[j][0] == temp1 && coordinates[j][1] == temp2) {
						unique = false;
						break;
					}
				}
			} while (!unique);

			coordinates[x][0] = temp1;
			coordinates[x][1] = temp2;
			refresh();
		}
	}
	
	void change_elem_list(int i, char x){
		elem_list[i] = x;
	}
};

void battlefield::manualcreate(){
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

	char temp_elem_list[max_robot_limit] = {};

	//----------------------Objects Selector--------------------------------
	cout << "Initializing map..." << endl;
	cout << "You have selected a " <<x_axis<<" x " << y_axis <<" map" <<endl;
	cout << "Select troops to march on an epic battle! Due to your battlefield size, you are limited to " << max_robot_limit <<" robots." << endl;
	int total_robot_count =0, this_robot_count = 0;
	for (int i = 0; i < 3; i++){ 
		cout << "How many " << all_robot_types[i] << "?" << endl;
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
				if (temp_elem_list[j] == '\0'){
					temp_elem_list[j] = all_robot_symbol_type_map.get(all_robot_types[i]);
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

	for (char each:temp_elem_list){
		if (each != '\0'){
			count+=1;
		}
	}

	elem_list = new char[count];
	for (int x = 0; x < count ; x++){
		elem_list[x] = temp_elem_list[x];
	}
	initialize_map();
	initialize_size_n_coords(count);
	randomize(elem_list);
	setup();

}

void battlefield::accessfile(){
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
	iss >> ignore >> elem_list_size;

	// Output the read values for verification
	cout << "x_axis: " << x_axis << " and y_axis: " << y_axis << endl;
	cout << "steps: " << target_steps << endl;
	cout << "elem_list_size: " << elem_list_size << endl;
	
	
	this->elem_list = new char[elem_list_size];
	this -> elem_name_list = new string[elem_list_size];
	initialize_map();
	initialize_size_n_coords(elem_list_size);
	// Read each robot data
	
	string elem, name, x, y;
	for (int i = 0; i < elem_list_size; ++i) {
		getline(file, line);
		istringstream iss(line);

		iss >> elem >> name >> x >> y;

		cout << "Robot " << i + 1 << ": " << elem << " " << name << " (" << x << ", " << y << ")" << endl;
		
		// Process coordinates
		if (x == "random" || y == "random") {
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
			x = to_string(temp1);
			y = to_string(temp2);
		}
		
		elem_list[i] = all_robot_symbol_type_map.get(elem);
		elem_name_list[i] = name;
		coordinates[i][0] = stoi(x);
		coordinates[i][1] = stoi(y);
		
	}

	setup();
}

// Base abstract class for all robots
class Robot {
protected:
    battlefield* gameMap;
	string name;
    int pos[2];
    int kills = 0;
    bool detect = false;
    int detectPos[2] = {0};
	int index;
	
public:
    Robot(battlefield* field, string name,int x, int y, int i){
		this -> gameMap = field; 
		this -> name = name;
		pos[0] = x;
		pos[1] = y;
		index = i;
	}

    // Pure virtual function to be overridden by subclasses
    virtual void operate() = 0;
	
	void refreshpos(int x, int y){
		pos[0] = x;
		pos[1] = y;
	}
	
	int checkkills(){
		return kills;
	}
	
	string showname(){
		return name;
	}
};

// Subclass for robots that can see
class SeeingRobot : virtual public Robot {
public:
    SeeingRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i) {}

    void operate() override {
        cout << name << " is performing a look...\n";
        for (int i = pos[0] - 1; i <= pos[0] + 1; i++)
        {
            for (int j = pos[1] - 1; j <= pos[1] + 1; j++)
            {
                if (j < 0 || j >= gameMap->getWidth() || i < 0 || i >= gameMap->getHeight()){
                    continue;
				}
                else if (i == pos[0] && j == pos[1])
                    continue;
                else
                {	
                    if (gameMap->checkoccupied(i, j))
                    {
                        detect = true;
						cout << "Terminator is at " << pos[0]  <<" " << pos[1] <<endl;
                        detectPos[0] = i;
                        detectPos[1] = j;
                        cout << "Target spotted at: " << detectPos[0] << "," << detectPos[1] << endl;
						return;
                    }
                }
            }
        }
    }
};

// Subclass for robots that can shoot
class ShootingRobot : virtual public Robot {
protected:
	int rotation = 0;
public:
    ShootingRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i) {
	}

    void operate() override {
		int targetx;
		int targety;
        do{
			targetx = rand()% gameMap->getWidth();
			targety = rand()% gameMap->getHeight();
		} while((targetx == pos[0] && targety == pos[1])|| targetx+targety > 10);
        cout << name << " has shot {" << targetx << ", " << targety << "} " << endl;
		if (gameMap->checkoccupied(targetx, targety))
		{
			gameMap->destroyElem(targetx, targety);
			gameMap->refresh();
			cout << name << " has killed the robot at {" << targetx << ", " << targety << "} " << endl;
			kills += 1;
		}
        return;
    }
	
	
	void fireclockwise() {
        int targetx = pos[0];
		int targety = pos[1];

        do
        {
            switch (rotation)
            {
            case 0:
                targety += 1;
                rotation++;
                break;
            case 1:
                targetx += 1;
                targety += 1;
                rotation++;
                break;
            case 2:
                targetx += 1;
                rotation++;
                break;
            case 3:
                targetx += 1;
                targety -= 1;
                rotation++;
                break;
            case 4:
                targety += -1;
                rotation++;
                break;
            case 5:
                targetx -= 1;
                targety -= 1;
                rotation++;
                break;
            case 6:
                targetx -= 1;
                rotation++;
                break;
            case 7:
                targetx -= 1;
                targety += 1;
                rotation = 0;
                break;
            default:
                break;
            }
            if (targetx < 0 || targetx >= gameMap->getWidth() || targety < 0 || targety >= gameMap->getHeight())
            {
                targetx = pos[0];
                targety = pos[1];
				continue;
            }
			break;
        } while (1);
        cout << name << " has shot {" << targetx << ", " << targety << "} " << endl;
		if (gameMap->checkoccupied(targetx, targety))
		{
			gameMap->destroyElem(targetx, targety);
			gameMap->refresh();
			cout << name <<" has killed the robot at {" << targetx << ", " << targety << "} " << endl;
			kills += 1;
		}
	}

	void firesurround() {
		int random;
		int count = 0;
		int targetx;
		int targety;
		random = rand()%8;
		for (int i = pos[0] - 1; i <= pos[0] + 1; i++)
		{
			for (int j = pos[1] - 1; j <= pos[1] + 1; j++){
				if (j < 0 || j >= gameMap->getWidth() || i < 0 || i >= gameMap->getHeight()){
					continue;
				}
				else if (i == pos[0] && j == pos[1])
					continue;
				else {
					if (count == random){
						targetx = i;
						targety = j;
						cout << name << " shoot at " << targetx <<"," << targety << endl;
						if (gameMap->checkoccupied(targetx, targety))
						{
							gameMap->destroyElem(targetx, targety);
							gameMap->refresh();
							cout << name <<" has killed the robot at {" << targetx << ", " << targety << "} " << endl;
							kills += 1;
						}
						break;
					}
				}						
			}
		}
	}
};

// Subclass for robots that can move
class MovingRobot : virtual public Robot {
public:
    MovingRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i) {
	}

    void operate() override {
        int targetx = pos[0];
        int targety = pos[1];
		int moves;
		do {
			moves = rand() % 8;
			switch (moves)
			{
			case 0:
				targety++; // Up
				break;
			case 1:
				targetx--; // Left
				break;
			case 2:
				targety--; // Down
				break;
			case 3:
				targetx++; // Right
				break;
			case 4:
				targetx--; // Up left
				targety++;
				break;
			case 5:
				targetx++; // Up right
				targety++;
				break;
			case 6:
				targetx--; // Down left
				targety--;
				break;
			case 7:
				targetx++; // Down right
				targety--;
				break;
			default:
				break;
			}
            if (targetx < 0 || targetx >= gameMap->getWidth() || targety < 0 || targety >= gameMap->getHeight()||gameMap->checkoccupied(targetx, targety) == true)
            {
                targetx = pos[0];
                targety = pos[1];
				continue;
            }
			break;
		} while (1);
		detectPos[0] = targetx;
		detectPos[1] = targety;
        pos[0] = targetx;
		pos[1] = targety;
		cout << "Set pos to " <<pos[0] << ", "<< pos[1]<<endl;
        gameMap->changecoords(index, pos);
    }
};

class SteppingRobot : virtual public Robot {
public:
    SteppingRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i) {	
	}

    void operate() override {
        if (detect){
            gameMap->destroyElem(detectPos[0], detectPos[1]);
			cout << name << " has terminated robot at "<< detectPos[0] << "," << detectPos[1] << endl;
			kills += 1;
            gameMap->changecoords(index, detectPos);
            pos[0] = detectPos[0];
			pos[1] = detectPos[1];
            detect = 0;
            gameMap->refresh();	
		} else {
			int targetx = pos[0];
			int targety = pos[1];
			int moves;
			do {
				moves = rand() % 8;
				switch (moves)
				{
				case 0:
					targety++; // Up
					break;
				case 1:
					targetx--; // Left
					break;
				case 2:
					targety--; // Down
					break;
				case 3:
					targetx++; // Right
					break;
				case 4:
					targetx--; // Up left
					targety++;
					break;
				case 5:
					targetx++; // Up right
					targety++;
					break;
				case 6:
					targetx--; // Down left
					targety--;
					break;
				case 7:
					targetx++; // Down right
					targety--;
					break;
				default:
					break;
				}
				if (targetx < 0 || targetx >= gameMap->getWidth() || targety < 0 || targety >= gameMap->getHeight()||gameMap->checkoccupied(targetx, targety) == true)
				{
					targetx = pos[0];
					targety = pos[1];
					continue;
				}
				break;
			} while (1);
			detectPos[0] = targetx;
			detectPos[1] = targety;
			pos[0] = targetx;
			pos[1] = targety;
			cout << "Set pos to " <<pos[0] << ", "<< pos[1]<<endl;
			gameMap->changecoords(index, pos);
		}
    }
};


// Example of a robot that can look once then shoot
class Robocop : public MovingRobot, public ShootingRobot {

public:
    Robocop(battlefield* field, string name,int x, int y, int i) 
	    : Robot(field, name, x, y, i), ShootingRobot(field, name, x, y, i), MovingRobot(field, name, x, y, i) {
	}



    void operate() override {
        MovingRobot::operate();
        ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
    }
};

class Terminator : public SeeingRobot, public SteppingRobot {
    int count;

public:
    Terminator(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),SeeingRobot(field,name,x,y,i), SteppingRobot(field,name,x,y,i), count(0) {}

    void operate() override {
        SeeingRobot::operate();
        SteppingRobot::operate();
    }
};

class BlueThunder : public ShootingRobot{
    int count;

public:
    BlueThunder(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),ShootingRobot(field,name,x,y,i), count(0) {}

    void operate() override {
        ShootingRobot::fireclockwise();
    }
};

class TerminatorRoboCop : public ShootingRobot, public SeeingRobot, public SteppingRobot {

public:
    TerminatorRoboCop(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),ShootingRobot(field,name,x,y,i), SeeingRobot(field,name,x,y,i), SteppingRobot(field,name,x,y,i){}

    void operate() override {
		ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
        SeeingRobot::operate();
        SteppingRobot::operate();
    }
};

class Madbot : public ShootingRobot {

public:
    Madbot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),ShootingRobot(field,name,x,y,i){}

    void operate() override {
		ShootingRobot::firesurround();  //code this
    }
};

class RoboTank : public ShootingRobot {

public:
    RoboTank(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),ShootingRobot(field,name,x,y,i){}

    void operate() override {
		ShootingRobot::operate();
    }
};

class UltimateRobot : public ShootingRobot, public SeeingRobot, public SteppingRobot {

public:
    UltimateRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),ShootingRobot(field,name,x,y,i), SeeingRobot(field,name,x,y,i), SteppingRobot(field,name,x,y,i){}

    void operate() override {
		ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
		ShootingRobot::operate();
        SeeingRobot::operate();
        SteppingRobot::operate();
    }
};




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
				if (game.checklives(i) != 0){
					cout << game.elem_list[i] << " is revived at " << game.getX(i) << "," << game.getY(i) << "!" << endl;
					cout << "Lives left: " << game.checklives(i) << endl << endl;
					robot_list[i]->refreshpos(game.getX(i),game.getY(i));
				}
			}
		}
	string all_robot_types[7] = {"RoboCop","Terminator","BlueThunder","TerminatorRoboCop","Madbot","RoboTank","UltimateRobot"};
	char all_robot_symbol[7] = {'R','T','B','A','M','E','U'};
        for (int i = 0; i < game.get_elem_list_size(); i++)
        {	
			if (game.checkrevive(i) == 0){
				robot_list[i]->operate();
				cout << endl;
				if (robot_list[i]->checkkills() >= 3){
					cout << robot_list[i]->showname() ;
					if (game.elem_list[i] == 'R'||game.elem_list[i] == 'T'){
						game.change_elem_list(i,'A');
						robot_list[i] = new TerminatorRoboCop(&game, "TerminatorRobocop", game.getX(i), game.getY(i), i);
					} else if (game.elem_list[i] == 'A'||game.elem_list[i] == 'E'){
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