#include "IN-DC.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <assert.h>
#include <fstream>
#include <stdio.h>  
#include <stdlib.h>
#include <limits.h>
using namespace std;
namespace ns3 {
/*
INDC::INDC (int nbees, int wsnnodes,double alpha, double beta, double q, double ro, double taumax,int initCity) {
	NUMBEROFbeeS 	= nbees;
	NUMBEROFnodes 	= wsnnodes;
	ALPHA 			= alpha;
	BETA 			= beta;
	Q 				= q;
	RO 				= ro;
	TAUMAX 			= taumax;
	INITIALCITY		= initCity;
}
INDC::~INDC () {
	for(int i=0; i<NUMBEROFnodes; i++) {
		delete [] GRAPH[i];
		delete [] nodes[i];
		delete [] PHEROMONES[i];
		delete [] DELTAPHEROMONES[i];
		if(i < NUMBEROFnodes - 1) {
			delete [] PROBS[i];
		}
	}
	delete [] GRAPH;
	delete [] nodes;
	delete [] PHEROMONES;
	delete [] DELTAPHEROMONES;
	delete [] PROBS;
}
*/
void INDC::init () {
	GRAPH 			= new int*[NUMBEROFnodes];
	nodes 			= new double*[NUMBEROFnodes];
	PHEROMONES 		= new double*[NUMBEROFnodes];
	DELTAPHEROMONES = new double*[NUMBEROFnodes];
	PROBS 			= new double*[NUMBEROFnodes-1];
	for(int i=0; i<NUMBEROFnodes; i++) {
		GRAPH[i] 			= new int[NUMBEROFnodes];
		nodes[i] 			= new double[2];
		PHEROMONES[i] 		= new double[NUMBEROFnodes];
		DELTAPHEROMONES[i] 	= new double[NUMBEROFnodes];
		PROBS[i] 			= new double[2];
		for (int j=0; j<2; j++) {
			nodes[i][j] = -1.0;
			PROBS[i][j]  = -1.0;
		}
		for (int j=0; j<NUMBEROFnodes; j++) {
			GRAPH[i][j] 			= 0;
			PHEROMONES[i][j] 		= 0.0;
			DELTAPHEROMONES[i][j] 	= 0.0;
		}
	}	

	ROUTES = new int*[NUMBEROFbeeS];
	for (int i=0; i<NUMBEROFbeeS; i++) {
		ROUTES[i] = new int[NUMBEROFnodes];
		for (int j=0; j<NUMBEROFnodes; j++) {
			ROUTES[i][j] = -1;
		}
	}
	
	BESTLENGTH = (double) INT_MAX;
	BESTROUTE  = new int[NUMBEROFnodes];
	for (int i=0; i<NUMBEROFnodes; i++) {
		BESTROUTE[i] = -1;	
	}
}


void INDC::connectnodes (int cityi, int cityj) {
	GRAPH[cityi][cityj] = 1;
	GRAPH[cityj][cityi] = 1;
	PHEROMONES[cityj][cityi] = PHEROMONES[cityi][cityj];
}
void INDC::setCITYPOSITION (int city, double x, double y) {
	nodes[city][0] = x;
	nodes[city][1] = y;
}
void INDC::printPHEROMONES () {		
	for (int i=0; i<NUMBEROFnodes; i++) {
		
	}
	
	for (int i=0; i<NUMBEROFnodes; i++) {
		
	}
	cout << endl;
	for (int i=0; i<NUMBEROFnodes; i++) {
		
		for (int j=0; j<NUMBEROFnodes; j++) {
			if (i == j) {
				
				continue;
			}
			if (exists(i, j)) {
				printf ("%7.3f ", PHEROMONES[i][j]);
			}
			else {
				if(PHEROMONES[i][j] == 0.0) {
					printf ("%5.0f   ", PHEROMONES[i][j]);
				}
				else {
					printf ("%7.3f ", PHEROMONES[i][j]);
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}


double INDC::distance (int cityi, int cityj) {
	return (double) 
		sqrt (pow (nodes[cityi][0] - nodes[cityj][0], 2) + 
 			  pow (nodes[cityi][1] - nodes[cityj][1], 2));
}
bool INDC::exists (int cityi, int cityc) {
	return (GRAPH[cityi][cityc] == 1);
}
bool INDC::vizited (int beek, int c) {
	for (int l=0; l<NUMBEROFnodes; l++) {
		if (ROUTES[beek][l] == -1) {
			break;
		}
		if (ROUTES[beek][l] == c) {
			return true;
		}
	}
	return false;
}
double INDC::PHI (int cityi, int cityj, int beek) {
	double ETAij = (double) pow (1 / distance (cityi, cityj), BETA);
	double TAUij = (double) pow (PHEROMONES[cityi][cityj],   ALPHA);

	double sum = 0.0;
	for (int c=0; c<NUMBEROFnodes; c++) {
		if (exists(cityi, c)) {
			if (!vizited(beek, c)) {
				double ETA = (double) pow (1 / distance (cityi, c), BETA);
				double TAU = (double) pow (PHEROMONES[cityi][c],   ALPHA);
				sum += ETA * TAU;
			}	
		}	
	}
	return (ETAij * TAUij) / sum;
}

double INDC::length (int beek) {
	double sum = 0.0;
	for (int j=0; j<NUMBEROFnodes-1; j++) {
		sum += distance (ROUTES[beek][j], ROUTES[beek][j+1]);	
	}
	return sum;
}

int INDC::city () {
double xi = 10;
	int i = 0;
	double sum = PROBS[i][0];
	while (sum < xi) {
		i++;
		sum += PROBS[i][0];
	}
	return (int) PROBS[i][1];
}

void INDC::route (int beek) {
	ROUTES[beek][0] = INITIALCITY;
	for (int i=0; i<NUMBEROFnodes-1; i++) {		
		int cityi = ROUTES[beek][i];
		int count = 0;
		for (int c=0; c<NUMBEROFnodes; c++) {
			if (cityi == c) {
				continue;	
			}
			if (exists (cityi, c)) {
				if (!vizited (beek, c)) {
					PROBS[count][0] = PHI (cityi, c, beek);
					PROBS[count][1] = (double) c;
					count++;
				}

			}
		}
				if (0 == count) {
			return;
		}
		
		ROUTES[beek][i+1] = city();
	}
}
int INDC::valid (int beek, int iteration) {
	for(int i=0; i<NUMBEROFnodes-1; i++) {
		int cityi = ROUTES[beek][i];
		int cityj = ROUTES[beek][i+1];
		if (cityi < 0 || cityj < 0) {
			return -1;	
		}
		if (!exists(cityi, cityj)) {
			return -2;	
		}
		for (int j=0; j<i-1; j++) {
			if (ROUTES[beek][i] == ROUTES[beek][j]) {
				return -3;
			}	
		}
	}
	
	if (!exists (INITIALCITY, ROUTES[beek][NUMBEROFnodes-1])) {
		return -4;
	}
	
	return 0;
}


void INDC::updatePHEROMONES () {
	for (int k=0; k<NUMBEROFbeeS; k++) {
		double rlength = length(k);
		for (int r=0; r<NUMBEROFnodes-1; r++) {
			int cityi = ROUTES[k][r];
			int cityj = ROUTES[k][r+1];
			DELTAPHEROMONES[cityi][cityj] += Q / rlength;
			DELTAPHEROMONES[cityj][cityi] += Q / rlength;
		}
	}
	for (int i=0; i<NUMBEROFnodes; i++) {
		for (int j=0; j<NUMBEROFnodes; j++) {
			PHEROMONES[i][j] = (1 - RO) * PHEROMONES[i][j] + DELTAPHEROMONES[i][j];
			DELTAPHEROMONES[i][j] = 0.0;
		}	
	}
}


void INDC::optimize (int ITERATIONS) {
	for (int iterations=1; iterations<=ITERATIONS; iterations++) {
		cout << flush;
		cout << "ITERATION " << iterations << " HAS STARTED!" << endl << endl;

		for (int k=0; k<NUMBEROFbeeS; k++) {
			cout << " : bee " << k << " has been released!" << endl;
			while (0 != valid(k, iterations)) {
				cout << "  :: releasing bee " << k << " again!" << endl;
				for (int i=0; i<NUMBEROFnodes; i++) {
					ROUTES[k][i] = -1;	
				}
				route(k);
			}
			
			for (int i=0; i<NUMBEROFnodes; i++) {
				cout << ROUTES[k][i] << " ";	
			}
			cout << endl;
			
			cout << "  :: route done" << endl;
			double rlength = length(k);

			if (rlength < BESTLENGTH) {
				BESTLENGTH = rlength;
				for (int i=0; i<NUMBEROFnodes; i++) {
					BESTROUTE[i] = ROUTES[k][i];
				}
			}
			cout << " : bee " << k << " has ended!" << endl;				
		}		

		
		updatePHEROMONES ();
		cout << " done!" << endl << endl;
		
		
		for (int i=0; i<NUMBEROFbeeS; i++) {
			for (int j=0; j<NUMBEROFnodes; j++) {
				ROUTES[i][j] = -1;
			}
		}

		
	}
}
}
