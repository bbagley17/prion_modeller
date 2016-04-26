#include <iostream>
#include "Cell.h"

using namespace std;

void Cell::checkCollision()
{
	//Scans through entire vesicle vector to see if any vesicles have collided with the cell
	for (int n = 0; n < vesicleVector.size(); n++)
	{
		if ((vesicleVector[n].xCrd == xCoord) && (vesicleVector[n].yCrd == yCoord) && (vesicleVector[n].zCrd == zCoord))
		{
			//Something that deletes the vector and adds its prions to the cell.
		}
	}
}

void Cell::createVesicle()
{
	if((prionCount/(3.14159 * radius * radius) < maxPrionDensity //parameter for the max number of prions/volume a cell can hold)
}

//Call ODE solver to model prion spread within cell
void Cell::prionSpread()
{

}
