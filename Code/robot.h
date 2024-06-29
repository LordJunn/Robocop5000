#ifndef ROBOT_H
#define ROBOT_H

#include <conio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
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
                if (j < 0 || j >= gameMap->getHeight() || i < 0 || i >= gameMap->getWidth()){
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
		} while((targetx == pos[0] && targety == pos[1])|| targetx + targety > 10);
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
				if (j < 0 || j >= gameMap->getHeight() || i < 0 || i >= gameMap->getWidth()){
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
		cout << name << " set pos to " <<pos[0] << ", "<< pos[1]<<endl;
        gameMap->changecoords(index, pos);
    }
};

class ExplodeRobot : virtual public Robot {
public:
    ExplodeRobot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i) {
	}

    void operate() override {
		int targetx;
		int targety;
        for (int i = pos[0] - 1; i <= pos[0] + 1; i++)
        {
            for (int j = pos[1] - 1; j <= pos[1] + 1; j++)
            {
                if (j < 0 || j >= gameMap->getHeight() || i < 0 || i >= gameMap->getWidth()){
                    continue;
				}
                else if (i == pos[0] && j == pos[1])
                    continue;
                else
                {	
                    if (gameMap->checkoccupied(i, j))
                    {
						cout << "Enemy detected. Self explode initiated!" << endl;
						for (int i2 = pos[0] - 1; i2 <= pos[0] + 1; i2++)
						{
							for (int j2 = pos[1] - 1; j2 <= pos[1] + 1; j2++)
							{
								if (j2 < 0 || j2 >= gameMap->getHeight() || i2 < 0 || i2 >= gameMap->getWidth()){
									continue;
								}
								else if (i2 == pos[0] && j2 == pos[1])
									continue;
								else
								{	
									targetx = i2;
									targety = j2;
									if (gameMap->checkoccupied(targetx, targety))
									{
										gameMap->destroyElem(targetx, targety);
										gameMap->refresh();
										cout << name <<"'s explosion has killed the robot at {" << targetx << ", " << targety << "} " << endl;
										kills += 1;
									}
								}
							}
						}
						gameMap->destroyElem(pos[0], pos[1]);
						gameMap->refresh();
						return;
                    }
                }
            }
        }
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
			cout << name << " set pos to " <<pos[0] << ", "<< pos[1]<<endl;
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

class ExplodoBot : public MovingRobot, public ExplodeRobot {

public:
    ExplodoBot(battlefield* field, string name,int x, int y, int i) : Robot(field,name,x,y,i),MovingRobot(field,name,x,y,i),ExplodeRobot(field,name,x,y,i){}

    void operate() override {
		MovingRobot::operate();
		ExplodeRobot::operate();
    }
};

#endif