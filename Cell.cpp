#include <iostream>
#include "Cell.h"
#include "Source.cpp"

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
	if ((prionCount / (3.14159 * radius * radius) < maxPrionDensity)) //parameter for the max number of prions/volume a cell can hold)
	{
		int content = 20000; //Exosomes contain an average of roughly 20,000 proteins.
		double xStart;
		double yStart;
		double zStart;
		do
		{

			xStart = rand()%(2*radius);
			yStart = rand()%(2*radius);
			zStart = rand()%(2*radius);
		} while ((sqrt((xStart * xStart)+(yStart * yStart) + (zStart * zStart)) > radius) && 
			(sqrt((xStart * xStart) + (yStart * yStart) + (zStart * zStart)) <= (radius + 0.1 *radius))); 
		/* This section above is a bit complicated. It's a rough approximation, but works. 
			Basically, the initial position of the vesicle is set randomly within two radii of the cell.
			If that position is outside the cells outer surface (more than 1 radius), but within 110% of the radius,
			the vesicle will be created at that site. If not, the coordinates will be reiterated. 

			It is important to note that the above is just a measure of magnitude. that is, it solves for a set of xyz magnitudes
			beyond the cell membrane. Below, these magnitudes will be given direction.
		*/
		
		// dir is randomly selected between 1 and six. This determines which of the six sites with the above xyz magnitudes at which
			//the vesicle will actually be created
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
}

//Call ODE solver to model prion spread within cell
void Cell::prionSpread()
{

}
