#ifndef RUNGEKUTTA_H
#define RUNGE KUTTA_H
void rungekutta(vector<Cell>* cellVector){
int numCells = cellVector.size();
double mindist = 1;
int numCellsClose = 0;
bool h** = new bool*[numCells]; // allocates 2d bool array
for (int i = 0; i < numCells; i++){
	bool* withinArray = (NULL);
	withinArray = new bool[numCells];
	h[i] = withinArray;
}


for (int i = 0; i < numCells; i++){
	for (int j = i + 1; j < numCells, j++){
		if (((cellVector.at(j).xCoord - cellVector.at(i).xCoord)*(cellVector.at(j).xCoord - cellVector.at(i).xCoord) + (cellVector.at(j).yCoord - cellVector.at(i).yCoord)*(cellVector.at(j).yCoord - cellVector.at(i).yCoord) + (cellVector.at(j).zCoord - cellVector.at(i).zCoord)*(cellVector.at(j).zCoord - cellVector.at(i).zCoord)) <= mindist*mindist) {
			h[i][j] = true;
			h[j][i] = true;
			numCellsClose++;
		} 
		else{
		h[i][j] = false;
		h[j][i] = false;
		}
	}
}

dt = .05; //timestep

double* k1 = new double(numCells); 
double* k2 = new double(numCells);
double* k3 = new double(numCells);
double* k4 = new double(numCells);

dt*f(h,k1,k2,k3,k4,1,numCells);
dt*f(h,k1,k2,k3,k4,2,numCells);
dt*f(h,k1,k2,k3,k4,3,numCells);
dt*f(h,k1,k2,k3,k4,4,numCells); 

for (int i = 0; i < numCells; i++){
	int temp = cellVector.at(i).prionCount + (k1[i] + 2*k2[i] + 2*k3[i] +k4)/6;
	cellVector.at(temp1[i]).cellVector(temp);
}
}


void f(bool* h,double* k1,double* k2,double* k3,double* k4,int cycle, int numCells){
	long double constant = .000000005;
	long double constant2 = .00000000000000005;
	for (int i = 0; i < numCells, i++){
		for (int j = 0; j < numCells, j++){
			switch(cycle){
				case 1:
				if (h[i][j] && (i !=j)){
					k1[i] +=  constant*cellVector.at(j).prionCount - contstant*cellVector.at(i).prionCount; //need to define what "constant" is
				}
				if (cellVector.at(i).prionCount > 0){
				k1[i] += -constant2*(cellVector.at(i).prionCount);
				}	
				case 2:
				if (h[i][j] && (i !=j)){
					k2[i] += constant*(cellVector.at(j).prionCount + .5*k1[j]) - contstant*(cellVector.at(i).prionCount + .5*k1[i]);
				}
				if (cellVector.at(i).prionCount > 0){
				k2[i] += -constant2*(cellVector.at(i).prionCount + .5*k1[i]);
				}
				case 3:
				if (h[i][j] && (i !=j)){
					k3[i] += constant*(cellVector.at(j).prionCount + .5*k2[j]) - contstant*(cellVector.at(i).prionCount + .5*k2[i]);
				}
				if (cellVector.at(i).prionCount > 0){
				k3[i] += -constant2*(cellVector.at(i).prionCount +.5*k2[i]);
				}
				case 4:
				if (h[i][j] && (i !=j)){
					k4[i] += constant*(cellVector.at(j).prionCount + k3[j]) - contstant*(cellVector.at(i).prionCount + k3[i]);
				}
				if (cellVector.at(i).prionCount > 0){
				k4[i] += -constant2*(cellVector.at(i).prionCount +k3[i]);
				}
			}
		}
	}
#endif
