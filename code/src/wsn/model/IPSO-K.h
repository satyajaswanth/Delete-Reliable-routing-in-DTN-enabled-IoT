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
typedef struct {
    double error;
    double *gbest;
} IPSO_K_result_t;
typedef double (*IPSO_K_obj_fun_t)(double *, int, void *);
typedef struct {
    int dim; 
    double x_lo; 
    double x_hi; 
    double goal; 
    int size; 
    int print_every; 
    int steps; 
    int step; 
    double c1; 
    double c2; 
    double w_max; 
    double w_min; 
    int clamp_pos; 
    int nhood_strategy; 
    int nhood_size;  
    int w_strategy; 
    void *rng; 
    long seed; 
} IPSO_K_settings_t;
class IPSO_K
{
int IPSO_K_calc_swarm_size(int dim);
void IPSO_K_set_default_settings(IPSO_K_settings_t *settings);
void IPSO_K_solve(IPSO_K_obj_fun_t obj_fun, void *obj_fun_params,IPSO_K_result_t *solution, IPSO_K_settings_t *settings);
};
}
#endif // IPSO_K_H_
