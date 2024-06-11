#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void accessfile() {
    int x_axis;
    int y_axis;
    int steps;
	string filename;
    int robot_list_length;
	
	
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
    iss >> ignore >> steps;

    // Read and process the "robots:" line
    getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> ignore >> robot_list_length;

    // Output the read values for verification
    cout << "x_axis: " << x_axis << " and y_axis: " << y_axis << endl;
    cout << "steps: " << steps << endl;
    cout << "robot_list_length: " << robot_list_length << endl;
	
	
	string robot_type_list[robot_list_length];
	string robot_name_list[robot_list_length];
	int coords[robot_list_length][2];
    // Read each robot data
	
	string elem, name, x, y;
    for (int i = 0; i < robot_list_length; ++i) {
        getline(file, line);
        istringstream iss(line);

        iss >> elem >> name >> x >> y;

        cout << "Robot " << i + 1 << ": " << elem << " " << name << " (" << x << ", " << y << ")" << endl;
        
        // Process coordinates
        if (x == "random" || y == "random") {
            x = "-1";
			y = "-1";
        }
		robot_type_list[i] = elem;
		robot_name_list[i] = name;
		coords[i][0] = stoi(x);
		coords[i][1] = stoi(y);
		
    }
}

int main() {
    accessfile();
    return 0;
}