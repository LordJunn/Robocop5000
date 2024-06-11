#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void accessfile(const string& filename) {
    int x_axis;
    int y_axis;
    int steps;
    int robot_list_length;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    
    // Read and process the "M by N : " line
    getline(file, line);
    istringstream iss(line);
    string ignore;
    iss >> ignore*4 >> x_axis >> y_axis;

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
/*
    // Read each robot data
    for (int i = 0; i < robot_list_length; ++i) {
        getline(file, line);
        istringstream iss(line);
        string elem, name, x, y;
        iss >> elem >> name >> x >> y;

        cout << "Robot " << i + 1 << ": " << elem << " " << name << " (" << x << ", " << y << ")" << endl;
        
        // Process coordinates
        if (x == "random" || y == "random") {
            // Handle random coordinates
            cout << "Coordinates: random" << endl;
        } else {
            int x_coord = stoi(x);
            int y_coord = stoi(y);
            cout << "Coordinates: (" << x_coord << ", " << y_coord << ")" << endl;
        }
    }*/
}

int main() {
    accessfile("lec_sample.txt");
    return 0;
}