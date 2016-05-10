#include <iostream>
#include <vector>
#include "Vesicle.h"

using namespace std;

#ifndef Cell_H_
#define Cell_H_
class Cell
{
private:
	bool alive;
	double prionCount;
	double xCoord;
	double yCoord;
	double zCoord;
	double radius;

public:
	//Default constructor for cells
	Cell()
	{
		//Unless actual values are input, just make a dead cell with no prions at default coordinates.
		alive = false;
		prionCount = 0;
		xCoord = 0;
		yCoord = 0;
		zCoord = 0;
	}
	//Actual functional cell constructor
	Cell(int inputPrionCount, double x, double y, double z)
	{
		prionCount = inputPrionCount;
		xCoord = x;
		yCoord = y;
		zCoord = z;
	}

	//Checks to see if any vesicles have collided with the cell's boundaries
	void checkCollision();

	//If prionCount/volume ration surpasses certain level, excrete a vesicle full of prions
	void createVesicle();

	//Function which will call the ODE solver and add prions to the internal count on the basis of propagation w/in the cell
	void prionSpread();

	//Once the cell is "dead"... not sure how to model this, actually. May remove this feature.
	void isDead();

}; 
#endif
