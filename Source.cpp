#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
int cellCount;
vector<Cell> cells;

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
		outputFile << cells[n].prionCount << endl;
		outputFile << cells[n].x << endl;
		outputFile << cells[n].y << endl;
		outputFile << cells[n].z << endl;
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
