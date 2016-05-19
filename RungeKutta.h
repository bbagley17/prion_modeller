#ifndef RUNGEKUTTA_H
#define RUNGE KUTTA_H
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Vesicle.h"

void f(vector<Cell>&, vector<vector<bool>>&, vector<double>&, vector<double>&, vector<double>&, vector<double>&, int, int );

void rungekutta(vector<Cell>& cellVector) // this function updates the prion values in the cells once per call.
{
	int numCells = cellVector.size(); // read number of cell's we're dealing with into an int
	double mindist = 2000; // this is the minimum distance value between cells for interaction to take place
	/*bool** h;
	h = new bool*[numCells]; // This did not work at all. No idea why, so we went to vectors. 
	for (int i = 0; i < numCells; i++) {
	bool* withinArray = (NULL);
	withinArray = new bool[numCells];
	h[i] = withinArray;
	for (int j = 0; j < numCells; j++)
	h.at(i).at(j) = 0;
	}*/
	vector<vector<bool>> h(numCells, vector<bool>(numCells)); // creates a numCells x numCells bool vector



	for (int i = 0; i < numCells; i++) {// fills 2-d vector h with data , so that h.at(i).at(j) = true if cell i and cell j are within mindist. this means tha h is semetric about the diagonal.
		for (int j = 0; j < numCells; j++) { //faster would be to j = i+1, but reverted for security
			if (((cellVector.at(j).xCoord - cellVector.at(i).xCoord)*(cellVector.at(j).xCoord - cellVector.at(i).xCoord) + (cellVector.at(j).yCoord - cellVector.at(i).yCoord)*(cellVector.at(j).yCoord - cellVector.at(i).yCoord) + (cellVector.at(j).zCoord - cellVector.at(i).zCoord)*(cellVector.at(j).zCoord - cellVector.at(i).zCoord)) <= (mindist*mindist)) {
				h.at(i).at(j) = true;
				//h.at(j).at(i) = true;
			}
			else {
				h.at(i).at(j) = false;
				//h.at(j).at(i) = false;
			}
		}
	}

	double dt = 1; //timestep for runge-kutta function

	vector<double> k1(numCells, 0); //these are the k1-4 matricies from the runge-kutta algorithm which contain the recursive derivatives
	vector<double> k2(numCells, 0);
	vector<double> k3(numCells, 0);
	vector<double> k4(numCells, 0);

	f(cellVector, h, k1, k2, k3, k4, 1, numCells); //This function takes the cell vector, the boolean matrix h created above, all the k vectors, an int telling it which step of the rk4 algorithm to perform, and the number of cells.
	for (int i = 0; i < numCells; i++)
		k1.at(i) = k1.at(i) * dt;
	f(cellVector, h, k1, k2, k3, k4, 2, numCells);
	for (int i = 0; i < numCells; i++)
		k1.at(i) = k1.at(i) * dt;
	f(cellVector, h, k1, k2, k3, k4, 3, numCells);
	for (int i = 0; i < numCells; i++)
		k3.at(i) = k3.at(i) * dt;
	f(cellVector, h, k1, k2, k3, k4, 4, numCells);
	for (int i = 0; i < numCells; i++)
		k4.at(i) = k4.at(i) * dt;


	for (int i = 0; i < numCells; i++) {
		//cout << cellVector.at(i).prionCount << " ";
		double temp = cellVector.at(i).prionCount + (k1.at(i) + 2 * k1.at(i) + 2 * k3.at(i) + k4.at(i)) / 6; // this updates the prion cell counts based on the k1-4 values according to the rk4 algorithm
		cellVector.at(i).prionCount = temp;
		//cout << cellVector.at(i).prionCount << endl;
	}
	
}



void f(vector<Cell>& cellVector, vector<vector<bool>>& h, vector<double>& k1, vector<double>& k2, vector<double>& k3, vector<double>& k4, int cycle, int numCells)
{
	long double constant = .000000000000000000000000000000000000000000000005; //this is an arbirary constant defining the flow rate between cells
	long double constant2 = .000000000000000000000000000000000000000000000000000000000000000000000000000000000000000005; // this is an arbitrary constant defining how fast cells can attack and "kill" prions
	for (int i = 0; i < numCells; i++) {
		switch (cycle) {// here the actual calculation of k1-4 begins. int cycle tells us which case to perform. This switch performs the ODE d(prioncount)/dt = -constant2(prioncount). this is and intra-cell process.
		case 1:
			if (cellVector.at(i).prionCount > 0) {
				k1.at(i) -= constant2*(cellVector.at(i).prionCount);
			}
		case 2:
			if (cellVector.at(i).prionCount > 0) {
				k1.at(i) -= constant2*(cellVector.at(i).prionCount + .5*k1.at(i));
			}
		case 3:
			if (cellVector.at(i).prionCount > 0) {
				k3.at(i) -= constant2*(cellVector.at(i).prionCount + .5*k1.at(i));
			}
		case 4:
			if (cellVector.at(i).prionCount > 0) {
				k4.at(i) -= constant2*(cellVector.at(i).prionCount + k3.at(i));
			}
		}
		for (int j = 0; j < numCells; j++) {// here we iterate over all values in the h matrix so as to get all the ins and outs of each cell
			switch (cycle) { //same deal here, but we do the ODE d(prionCount)/dt = -numCellsWithinMindist*constant*prionCount + constant*connectedCell1.prioncount + connectedCell2.prioncount .... for all connected cells. This is an inter-cell process.
			case 1:
				if (h.at(i).at(j) && (i != j)) {
					k1.at(i) += (constant*cellVector.at(j).prionCount - constant*cellVector.at(i).prionCount); //need to define what "constant" is
				}
			case 2:
				if (h.at(i).at(j) && (i != j)) {
					k1.at(i) += (constant*(cellVector.at(j).prionCount + .5*k1.at(j)) - constant*(cellVector.at(i).prionCount + .5*k1.at(i)));
				}
			case 3:
				if (h.at(i).at(j) && (i != j)) {
					k3.at(i) += (constant*(cellVector.at(j).prionCount + .5*k2.at(j)) - constant*(cellVector.at(i).prionCount + .5*k1.at(i)));
				}
			case 4:
				if (h.at(i).at(j) && (i != j)) {
					k4.at(i) += (constant*(cellVector.at(j).prionCount + k3.at(j)) - constant*(cellVector.at(i).prionCount + k3.at(i)));
				}
			}
		}
	}
}
#endif
