#include <iostream>
#include <vector>
#include "Cell.h"
#include "Vesicle.h"

using namespace std;

void Vesicle::randomWalk()
{
	//Values for whether the vesicle will move in the positive or negative x,y,z directions, respetively
	int xPlusMinus = 0;
	int yPlusMinus = 0;
	int zPlusMinus = 0;
	//Magnitudes of the movement the vesicle will perform in each direction
	double xMagnitude;
	double yMagnitude;
	double zMagnitude;

	//For each "plusminus" value, if the value is 0, the vesicle moves in "-" direction. If 1, vesicle moves in "+" direction
	// if the value is 2, the vesicle is stationary in that axis
	xPlusMinus = rand() % 3;
	yPlusMinus = rand() % 3;
	zPlusMinus = rand() % 3;

	//Set the magnitude of the random step in each direction as some decimal between 0 and 1
	xMagnitude = 10;//(rand() % 100) / 100;
	yMagnitude = 10;//(rand() % 100) / 100;
	zMagnitude = 10;//(rand() % 100) / 100;

	//Updating each coordinate as a random walk
	if (xPlusMinus = 0)
		xCrd = xCrd - xMagnitude;
	if (xPlusMinus = 1)
		xCrd = xCrd + xMagnitude;


	if (yPlusMinus = 0)
		yCrd = yCrd - yMagnitude;
	if (yPlusMinus = 1)
		yCrd = yCrd + yMagnitude;

	if (zPlusMinus = 0)
		zCrd = xCrd - zMagnitude;
	if (zPlusMinus = 1)
		zCrd = xCrd + zMagnitude;

	

	
}
