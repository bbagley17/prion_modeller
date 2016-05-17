#ifndef RUNGEKUTTA_H
#define RUNGE KUTTA_H
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Vesicle.h"

void f(vector<Cell>& cellVector, bool h[][7], double* k1, double* k2, double* k3, double* k4, int cycle, int numCells);

void rungekutta(vector<Cell>& cellVector) 
{
	int numCells = cellVector.size();
	double mindist = 1;
	int numCellsClose = 0;
	/*bool** h;
	h = new bool*[numCells]; // allocates 2d bool array
	for (int i = 0; i < numCells; i++) {
		bool* withinArray = (NULL);
		withinArray = new bool[numCells];
		h[i] = withinArray;
		for (int j = 0; j < numCells; j++)
			h[i][j] = 0;
	}*/
	bool h[7][7];



	for (int i = 0; i < numCells; i++) {
		for (int j = i + 1; j < numCells; j++) {
			if (((cellVector.at(j).xCoord - cellVector.at(i).xCoord)*(cellVector.at(j).xCoord - cellVector.at(i).xCoord) + (cellVector.at(j).yCoord - cellVector.at(i).yCoord)*(cellVector.at(j).yCoord - cellVector.at(i).yCoord) + (cellVector.at(j).zCoord - cellVector.at(i).zCoord)*(cellVector.at(j).zCoord - cellVector.at(i).zCoord)) <= mindist*mindist) {
				h[i][j] = true;
				h[j][i] = true;
				numCellsClose++;
			}
			else {
				h[i][j] = false;
				h[j][i] = false;
			}
		}
	}

	double dt = 1; //timestep

	double k1[4] = { 0 };
	double k2[4] = { 0 };
	double k3[4] = { 0 };
	double k4[4] = { 0 };

	f(cellVector, h, k1, k2, k3, k4, 1, numCells);
	for (int i = 0; i < numCells; i++)
		k1[i] = k1[i] * dt;
	f(cellVector, h, k1, k2, k3, k4, 2, numCells);
	for (int i = 0; i < numCells; i++)
		k2[i] = k2[i] * dt;
	f(cellVector, h, k1, k2, k3, k4, 3, numCells);
	for (int i = 0; i < numCells; i++)
		k3[i] = k3[i] * dt;
	f(cellVector, h, k1, k2, k3, k4, 4, numCells);
	for (int i = 0; i < numCells; i++)
		k4[i] = k4[i] * dt;



	for (int i = 0; i < numCells; i++) {
		cout << cellVector.at(i).prionCount << " ";
		double temp = cellVector.at(i).prionCount + (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
		cellVector.at(i).prionCount = temp;
		cout << cellVector.at(i).prionCount << endl;
	}
}



void f(vector<Cell>& cellVector, bool h[][7], double* k1, double* k2, double* k3, double* k4, int cycle, int numCells)
{
	long double constant = .000000005;
	long double constant2 = .00000000000000005;
	for (int i = 0; i < numCells; i++) {
		switch (cycle) {
		case 1:
			if (cellVector.at(i).prionCount > 0) {
				k1[i] += -constant2*(cellVector.at(i).prionCount);
			}
		case 2:
			if (cellVector.at(i).prionCount > 0) {
				k2[i] += -constant2*(cellVector.at(i).prionCount + .5*k1[i]);
			}
		case 3:
			if (cellVector.at(i).prionCount > 0) {
				k3[i] += -constant2*(cellVector.at(i).prionCount + .5*k2[i]);
			}
		case 4:
			if (cellVector.at(i).prionCount > 0) {
				k4[i] += -constant2*(cellVector.at(i).prionCount + k3[i]);
			}
		}
		for (int j = 0; j < numCells; j++) {
			switch (cycle) {
			case 1:
				if (h[i][j] && (i != j)) {
					k1[i] += (constant*cellVector.at(j).prionCount - constant*cellVector.at(i).prionCount); //need to define what "constant" is
				}
			case 2:
				if (h[i][j] && (i != j)) {
					k2[i] += (constant*(cellVector.at(j).prionCount + .5*k1[j]) - constant*(cellVector.at(i).prionCount + .5*k1[i]));
				}
			case 3:
				if (h[i][j] && (i != j)) {
					k3[i] += (constant*(cellVector.at(j).prionCount + .5*k2[j]) - constant*(cellVector.at(i).prionCount + .5*k2[i]));
				}
			case 4:
				if (h[i][j] && (i != j)) {
					k4[i] += (constant*(cellVector.at(j).prionCount + k3[j]) - constant*(cellVector.at(i).prionCount + k3[i]));
				}
			}
		}
	}
}
#endif
