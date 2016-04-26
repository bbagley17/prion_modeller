#pragma once
#include <iostream>

using namespace std;

#ifndef Vesicle_H_
#define Vesicle_H_
class Vesicle
{
private:
	int prionCnt;
	double xCrd;
	double yCrd;
	double zCrd;

public:
	Vesicle(int prionInput, double startX, double startY, double startZ)
	{
		prionCnt = prionInput;
		xCrd = startX;
		yCrd = startY;
		zCrd = startZ;
	}

	void randomWalk();
};
#endif
