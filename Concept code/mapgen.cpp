#include <conio.h>
#include <iostream>
#include <string>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

int main(){
	int x_axis, y_axis, temp;
	bool escape;
	// ----------------------Map Axis Getter + set all to empty-----------------------------------
	cout << "Enter x-axis: " ;
	cin >> x_axis;
	cout << "Enter y-axis: "; 
	cin >> y_axis;
	char array[x_axis][y_axis] = {};
	for (int x=  0;x < x_axis;x++){
		for (int y= 0; y< y_axis; y++){
			array[x][y] = ' ';
		}
	}
	//---------------------- end of Map Axis Getter + set all to empty-----------------------------------
	//------------------------Random robot placing-------------------------------------
	int robotR_x_axis, robotR_y_axis;
	robotR_x_axis = rand()%x_axis;
	robotR_y_axis = rand()%y_axis;
	array[robotR_x_axis][robotR_y_axis] = 'R';
	cout << "Robot R is generated at " << robotR_x_axis << " " << robotR_y_axis <<endl << "--Press Enter to continue!--";
	getch();
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
	for (int some=  0;some < 300;some++){
		//----------------------------map generator/shower-----------------------------------------
		if (system("CLS")) system("clear");
		cout << "+" ;
		for (int z= 0;z < x_axis;z++){
			cout << "---+" ;
		}	
		cout << endl; 	
		for (int y= 0; y<y_axis; y++){
			for (int x= 0; x<x_axis; x++){
				if (x == targetx && y == targety){
					cout << "|[" << array[x][y] <<"]";
				} else
				cout << "| " << array[x][y] <<" ";
			}
			cout << "|" <<endl;
			for (int x= 0; x<x_axis; x++){
				cout << "+---";
			}		
			cout << "+" << endl;
		}
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