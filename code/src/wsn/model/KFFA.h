#ifndef IPSO_K_H_
#define IPSO_K_H_
#define IPSO_K_MAX_SIZE 100 
#define IPSO_K_INERTIA 0.7298 
#define IPSO_K_NHOOD_GLOBAL 0
#define IPSO_K_NHOOD_RING 1
#define IPSO_K_NHOOD_RANDOM 2
#define IPSO_K_W_CONST 0
#define IPSO_K_W_LIN_DEC 1
namespace ns3 {
class KFFA
{
public:
double alpha_new(double alpha, int NGen);
void init_ffa();
void sort_ffa();
void replace_ffa();
void findlimits(int k);
void move_ffa();
int main(int argc, char* argv[]);
void dump_ffa(int gen);
/////////////////////////////////////////////////////double cost(double* sol);
double sphere(double* sol) ;
};
}
#endif 
