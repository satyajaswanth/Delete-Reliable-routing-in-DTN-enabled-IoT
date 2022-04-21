#ifndef INDC_H
#define INDC_H


namespace ns3 {
class INDC {
public:
	///INDC (int nbees, int wsnnodes, double alpha, double beta, double q, double ro, double taumax,int initCity);
///	virtual ~INDC();
	
	void init ();
	
	void connectnodes (int cityi, int cityj);
	void setCITYPOSITION (int city, double x, double y);
	
	
	         void printPHEROMONES();
	void optimize (int ITERATIONS);

private:
	double distance (int cityi, int cityj);
	bool exists (int cityi, int cityc);
	bool vizited (int beek, int c);
	double PHI (int cityi, int cityj, int beek);
	
	double length (int beek);
	
	int city ();
	void route (int beek);
	int valid (int beek, int iteration);
	
	void updatePHEROMONES ();

	
	int NUMBEROFbeeS, NUMBEROFnodes, INITIALCITY;
	double ALPHA, BETA, Q, RO, TAUMAX;
	
	double BESTLENGTH;
	int *BESTROUTE;

	int **GRAPH, **ROUTES;
	double **nodes, **PHEROMONES, **DELTAPHEROMONES, **PROBS;

	
};

}
#endif 

