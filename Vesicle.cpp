#include <iostream>
#include <vector>
#include "Cell.h"
#include "Vesicle.h"

using namespace std;

void Vesicle::randomWalk()
{
	//Values for whether the vesicle will move in the positive or negative x,y,z directions, respetively
	int xPlusMinus;
	int yPlusMinus;
	int zPlusMinus;
	//Magnitudes of the movement the vesicle will perform in each direction
	double xMagnitude;
	double yMagnitude;
	double zMagnitude;

	//For each "plusminus" value, if the value is 0, the vesicle moves in "-" direction. If 1, vesicle moves in "+" direction 
	xPlusMinus = rand() % 2;
	yPlusMinus = rand() % 2;
	zPlusMinus = rand() % 2;

	//Set the magnitude of the random step in each direction as some decimal between 0 and 1
	xMagnitude = 100;//(rand() % 100) / 100;
	yMagnitude = 100;//(rand() % 100) / 100;
	zMagnitude = 100;//(rand() % 100) / 100;

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
