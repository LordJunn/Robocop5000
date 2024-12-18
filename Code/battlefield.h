/* *********************************************************************
PROGRAM : battlefield.h
COURSE: OOPDS
TRIMESTER: 2410
LECTURE SESSION: TC1L
TUTORIAL SESSION: TT2L
GROUP: 3

Member 1
Name: Chee Rui
ID: 1211112287

Member 2
Name: Andrew Wee Hong Jun
ID: 1211108270

Member 3
Name: Mei Yong Peng
ID: 1211109159

Member 4
Name: Low Junn Kit
ID: 1211111305

Member 5
Name: Fong Kai Chun
ID: 1211108430

Member 6
Name: Chan Ka Ken 
ID: 1211109440

********************************************************************* */


#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "print.h"

#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <cctype>
#include <time.h> 

extern std::ofstream resultfile;

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
				if (lowercase(arrayAptr[i]) == lowercase(x)){
					return arrayBptr[i];
				}
			}
			throw std::logic_error(string("Array B Key not found")) ;
		}
		T1 get(T2 x){
			for (int i = 0; i < Arraysize; i++){
				if (lowercase(arrayAptr[i]) == lowercase(x)){
					return arrayAptr[i];
				}
			}
			throw std::logic_error(string("Array A Key not found")) ;
		}
		string lowercase(string a){
			transform(a.begin(), a.end(), a.begin(),[](unsigned char c){ return tolower(c); });
			return a;
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
	ofstream resultfile;
	
    char** map; // 2D array of the map

    string logs; // Logs
    string mapstring; // used to print the map
	
	
	string all_robot_types[8] = {"RoboCop","Terminator","BlueThunder","ExplodoBot","TerminatorRoboCop","Madbot","RoboTank","UltimateRobot"};
	char all_robot_symbol[8] = {'R','T','B','X','A','M','E','U'};
	
	mapper<string,char> all_robot_symbol_type_map = mapper<string,char>(all_robot_types,all_robot_symbol,8);
	
	bool custom_name = 0;

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
    void randomize(char* elem_list, string* elem_name_list) {
	
        this->elem_list = elem_list;
		this->elem_name_list = elem_name_list;

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
        print("Element ",elem_list[index]," is at {",coordinates[index][0],", ",coordinates[index][1],"}\n");
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
            if (revivecount[i] > 0){
				logs += elem_name_list[i];
				if (coordinates[i][0] != -99){
					logs += " is at {";
					logs += to_string(coordinates[i][0]);
					logs += ", ";
					logs += to_string(coordinates[i][1]);
					logs += "}\n";
				} else {
					logs += " is temporary dead\n";
				}
			}
        }
    }

    void printlogs() {
        print(logs);
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
        print(mapstring);
		print("\n");
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
	
	int get_steps(){
		return target_steps;
	}
	
	void change_elem_list(int i, char x){
		elem_list[i] = x;
	}

	string get_name(int i){
		return elem_name_list[i];
	}
	
	bool check_custom(){
		return custom_name;
	}
};

void battlefield::manualcreate(){
	target_steps = 9999;
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
	string temp_elem_name_list[max_robot_limit] = {};
	//----------------------Objects Selector--------------------------------
	cout << "Initializing map..." << endl;
	cout << "You have selected a " <<x_axis<<" x " << y_axis <<" map" <<endl;
	cout << "Select troops to march on an epic battle! Due to your battlefield size, you are limited to " << max_robot_limit <<" robots." << endl;
	int total_robot_count =0, this_robot_count = 0;
	for (int i = 0; i < 4; i++){ 
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
					temp_elem_list[j] = all_robot_symbol[i];
					temp_elem_name_list[j] = all_robot_types[i];
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
	elem_name_list = new string[count];
	for (int x = 0; x < count ; x++){
		elem_list[x] = temp_elem_list[x];
		elem_name_list[x] =  temp_elem_name_list[x];
	}
	initialize_map();
	initialize_size_n_coords(count);
	randomize(elem_list, elem_name_list);
	setup();

}

void battlefield::accessfile(){
	string filename;

	do {
		cout << "Enter filename: ";
		cin >> filename;
		filename = "Inputs/"+filename;
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
	file.close();
	custom_name = 1;
	
	setup();
}
#endif