#include <iostream>
#include "Cell.h"
#include "Vesicle.h"


using namespace std;

void Cell::checkCollision(vector<Vesicle>& vesicleVector, int& vesicleCount)
{
	//Scans through entire vesicle vector to see if any vesicles have collided with the cell
	for (int n = 0; n < vesicleVector.size(); n++)
	{
	//
		//
		//
		//Change this to check if the vesicle is within a range of the cell's coordinates. As is, of course it doesn't work.
		if ((vesicleVector[n].xCrd == xCoord) && (vesicleVector[n].yCrd == yCoord) && (vesicleVector[n].zCrd == zCoord))
		{
			prionCount += vesicleVector[n].prionCnt;
			vesicleVector.erase(vesicleVector.begin() + n);
			vesicleCount--;
		}
	}
}

void Cell::createVesicle(vector<Vesicle>& vesicleVector, int& vesicleCount)
{
	
		int content = 20000; //Exosomes contain an average of roughly 20,000 proteins.
		double xStart = 600;
		double yStart = 600;
		double zStart = 600;
		
		int dir = rand()%8;

		if (dir == 0)
		{
			xStart = xCoord + xStart;
			yStart = yCoord + yStart;
			zStart = zCoord + zStart;
		}
		else if (dir == 1)
		{
			xStart = xCoord - xStart;
			yStart = yCoord + yStart;
			zStart = zCoord + zStart;
		}
		else if (dir == 2)
		{
			xStart = xCoord + xStart;
			yStart = yCoord - yStart;
			zStart = zCoord + zStart;
		}
		else if (dir == 3)
		{
			xStart = xCoord + xStart;
			yStart = yCoord + yStart;
			zStart = zCoord - zStart;
		}
		else if (dir == 4)
		{
			xStart = xCoord - xStart;
			yStart = yCoord - yStart;
			zStart = zCoord + zStart;
		}
		else if (dir == 5)
		{
			xStart = xCoord + xStart;
			yStart = yCoord - yStart;
			zStart = zCoord - zStart;
		}
		else if (dir == 6)
		{
			xStart = xCoord - xStart;
			yStart = yCoord + yStart;
			zStart = zCoord - zStart;
		}
		else if (dir == 7)
		{
			xStart = xCoord - xStart;
			yStart = yCoord - yStart;
			zStart = zCoord - zStart;
		}

		//Creating the new exosome vesicle, iterating the vesicleCount;
		vesicleVector.push_back(Vesicle(content, xStart, yStart, zStart));
		vesicleCount++;
		//Removing the excreted prions from the cell's tally
		prionCount = prionCount - content;
	
}

//Call ODE solver to model prion spread within cell
void Cell::prionSpread()
{

}
