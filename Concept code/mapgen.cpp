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
	char array[3][3] = {{' ',' ','T'},{' ','R',' '},{'T',' ',' '}};
	int targetx, targety;
	for (int x=  0;x < 3;x++){
		for (int y= 0; y<3; y++){
			if (array[x][y] == 'R'){
				targetx = x;
				targety = y;
			}
		}
	}
	for (int some=  0;some < 300;some++){
		if (system("CLS")) system("clear");
		cout << "+" ;
		for (int z= 0;z < 3;z++){
			cout << "---+" ;
		}	
		cout << endl; 	
		for (int x=  0;x < 3;x++){
			for (int y= 0; y<3; y++){
				if (x == targetx && y == targety){
					cout << "|[" << array[x][y] <<"]";
				} else
				cout << "| " << array[x][y] <<" ";
			}
			cout << "|" <<endl;
			for (int a= 0; a<3; a++){
				cout << "+---";
			}		
			cout << "+" << endl;
		}
		getch(); //This is because it will always send two "Stuff" at the time, and the first stuff is always useless (for arrow keys)
		switch(getch()) { // the real value
			case 72: //left
				targetx -= 1;
				break;
			case 80: //down
				targetx += 1;
				break;
			case 77: //right
				targety += 1;
				break;
			case 75: //left
				targety -= 1;
				break;
		}
	}
	
}