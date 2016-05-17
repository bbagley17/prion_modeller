#include <iostream>
#include <vector>
#include "Vesicle.h"

using namespace std;

#ifndef Cell_H_
#define Cell_H_
class Cell
{
public:
	double maxPrionDensity = 80000;
	bool alive;
	double prionCount;
	double xCoord;
	double yCoord;
	double zCoord;
	int radius;

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
		alive = true;
		prionCount = inputPrionCount;
		xCoord = x;
		yCoord = y;
		zCoord = z;
		radius = 500; //This is simply a product of using the diameter of an exosome (excreted vesicle), 100nm as the reference value
			//So where a vesicle is 1 unit in diameter, the Cell is 1000 units (each of 100nm) in diameter, which neurons are
	}

	//Checks to see if any vesicles have collided with the cell's boundaries
	void checkCollision(vector<Vesicle>& vesicleVector, int& vesicleCount);



	//If prionCount/volume ratio surpasses certain level, excrete a vesicle full of prions
	void createVesicle(vector<Vesicle>& vesicleVector, int& vesicleCount);


	//Function which will call the ODE solver and add prions to the internal count on the basis of propagation w/in the cell
	void prionSpread();

	//Once the cell is "dead"... not sure how to model this, actually. May remove this feature.
	void isDead();


};
#endif
