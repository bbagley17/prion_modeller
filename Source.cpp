#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Cell.h"
#include "Vesicle.h"
#include "RungeKutta.h"

using namespace std;
void initializer();
void timeStep();
void output();

//Constant for spread rate of prions within cell
double c1 = 0.005;
int cellCount;
vector<Cell> cellVector;
int vesicleCount;
vector<Vesicle> vesicleVector;


int main()
{
	initializer();
	timeStep();
	output();
}

void timeStep()
{
	//Total time over which simulation will be run.
	int timeFrame;
	cout << "Please enter the total simulation time: " << endl;
	cin >> timeFrame;
	cout << endl;

	//Variables to be used for ticking off every 100 timesteps, after which the sim's state is output.
	int outputStep = 100;
	int elapsed = 0;

	for (int n = 0; n < timeFrame; n++)
	{
		//Stuff that iterates Luke's ODEs, stuff the iterates vesicle creation and propagation
		//rungekutta(cellVector);

		//Small bit of code to model spread of prions within cell, and creation of vesicles, and checks for 
		// vesicle-cell collisions
		for (int q = 0; q < cellCount; q++)
		{
			cellVector[q].prionCount += c1 * cellVector[q].prionCount;
			if ((cellVector[q].prionCount > cellVector[q].maxPrionDensity)) //parameter for the max number of prions/volume a cell can hold)
			{
				cellVector[q].createVesicle(vesicleVector, vesicleCount);
			}

			cellVector[q].checkCollision(vesicleVector, vesicleCount);
		}
		//For each vesicle, iterates the thermodynamic movement of the vesicle 
		for (int q = 0; q < vesicleCount; q++)
		{
			vesicleVector[q].randomWalk();

			//If the vesicle moves a certain distance away from the entire population of cells, 
			// that vesicle is simply deleted to reduce computational cost
			bool close = false;
			for (int z = 0; z < cellCount; z++)
			{
				if (2000 > abs(vesicleVector[q].xCrd - cellVector[z].xCoord))
				{
					close = true;
				}
				if (2000 > abs(vesicleVector[q].yCrd - cellVector[z].yCoord))
				{
					close = true;
				}
				if (2000 > abs(vesicleVector[q].zCrd - cellVector[z].xCoord))
				{
					close = true;
				}
			}
			if (close == false)
			{
				vesicleVector.erase(vesicleVector.begin() + q);
				vesicleCount--;
			}
		}

		//This is the code mentioned above, which outputs the current state of the simulation every (outputStep) timesteps
		if (elapsed == outputStep)
		{
			cout << "t: " << n << endl;
			//Outputting the values associated with each vesicle and cell, mainly for debugging purposes.
			//May be commented out for actual runs, unless desired. 
			cout << "cells" << endl;
			for (int q = 0; q < cellCount; q++)
			{
				cout << cellVector[q].prionCount << endl;
			}
			cout << "vesicles (x,y,z)" << endl;
			for (int q = 0; q < vesicleCount; q++)
			{
				cout << vesicleVector[q].xCrd << ", " << vesicleVector[q].yCrd << ", " << vesicleVector[q].zCrd << endl;
			}
			elapsed = 0;
		}
		else if (elapsed != outputStep)
		{
			elapsed++;
		}

	}
	

}
void output()
{
	string outputName;
	cout << "Please enter a file name under which the output will be saved:" << endl;
	cin >> outputName;
	cout << endl;

	ofstream outputFile;
	outputFile.open(outputName);
	if (outputFile.fail())
	{
		cout << "Filename not allowed." << endl;
		string outputName;
		cout << "Please enter a file name under which the output will be saved:" << endl;
		cin >> outputName;
		cout << endl;
		outputFile.open(outputName);
	}

	for (int n = 0; n < cellCount; n++)
	{
		outputFile << cellVector[n].prionCount << endl;
		outputFile << cellVector[n].xCoord << endl;
		outputFile << cellVector[n].yCoord << endl;
		outputFile << cellVector[n].zCoord << endl;
	}
	outputFile.close();
}
void initializer()
{
	string inputFileName;
	cout << "Please enter the name of the initialization file:" << endl;
	cin >> inputFileName;
	cout << endl;
	ifstream input;
	input.open(inputFileName);
	bool woops = false;
	if (input.fail())
	{
		woops = true;
	}
	while (woops == true)
	{
		cout << "File not found." << endl;
		cout << "Please enter the name of the initialization file:" << endl;
		cin >> inputFileName;
		cout << endl;
		ifstream input;
		input.open(inputFileName, ios::in);
		if (input.fail())
		{
			woops = true;
		}
		else
		{
			woops = false;
		}
	}
	
	/*ifstream input;
	input.open("new2.txt", ios::in);
	string line;
	*/
	int cells = 0;
	input >> cells;
	for (int n = 0; n < cells; n++)
	{
		double inputPrionCount;
		double x;
		double y;
		double z;


		input >> inputPrionCount;
		input >> x;
		input >> y;
		input >> z;


		cellVector.push_back(Cell(inputPrionCount, x, y, z));
		cellCount++;
	}

	for (int n = 0; n < cellCount; n++)
	{
		cout << "Cell " << n << " has prion count of:" << cellVector[n].prionCount << endl;
		cout << "Coordinates of " << cellVector[n].xCoord << ", " << cellVector[n].yCoord << ", " << cellVector[n].zCoord << endl;
	}
	input.close();
}
