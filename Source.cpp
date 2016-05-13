#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Cell.h"
#include "Vesicle.h"

using namespace std;
int cellCount;
vector<Cell> cellVector;
int vesicleCount;
vector<Vesicle> vesicleVector;

void initializer();
void timeStep();
void output();

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

	for (int n = 0; n < timeFrame; n++)
	{
		//Stuff that iterates Luke's ODEs, stuff the iterates vesicle creation and propagation

		//For each vesicle, iterates the thermodynamic movement of the vesicle 
		for (int q = 0; q < vesicleCount; q++)
		{
			vesicleVector[q].randomWalk();
		}

		//For each cell, checks whether a vesicle needs to be created and, if so, creates one
		for (int v = 0; v < vesicleCount; v++)
		{
			cellVector[v].createVesicle();
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
}
void initializer()
{
	string inputFileName;
	cout << "Please enter the name of the initialization file:" << endl;
	cin >> inputFileName;
	cout << endl;
	ifstream input;
	input.open(inputFileName);
	for (input.fail())
	{
		cout << "File not found." << endl;
		cout << "Please enter the name of the initialization file:" << endl;
		cin >> inputFileName;
		cout << endl;
		ifstream input;
		input.open(inputFileName);
	}
	string line;
	while (getline(input, line))
	{
		bool alive;
		double inputPrionCount;
		double x;
		double y;
		double z;

		input >> inputPrionCount;
		input >> x;
		input >> y;
		input >> z;

		Cell(inputPrionCount, x, y, z);
		cellCount++;
	}
}
