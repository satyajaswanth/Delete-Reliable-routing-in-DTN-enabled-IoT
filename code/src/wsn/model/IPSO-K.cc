#include <time.h> 
#include <math.h>
#include <float.h> 
#include <string.h> 
#include <gsl/gsl_rng.h>
#include "IPSO-K.h"
namespace ns3 {
int IPSO_K::IPSO_K_calc_swarm_size(int dim) {
    int size = 10. + 2. * sqrt(dim);
    return (size > IPSO_K_MAX_SIZE ? IPSO_K_MAX_SIZE : size);
}
double IPSO_K::calc_inertia_lin_dec(int step, IPSO_K_settings_t *settings) {
    int dec_stage = 3 * settings->steps / 4;
    if (step <= dec_stage)
	return settings->w_min + (settings->w_max - settings->w_min) *	\
	    (dec_stage - step) / dec_stage;
    else
	return settings->w_min;
}
void IPSO_K::inform_global(int *comm, double *pos_nb,double *pos_b, double *fit_b,double *gbest, int improved,IPSO_K_settings_t *settings)
{
    int i;
    for (i=0; i<settings->size; i++)
	memmove((void *)&pos_nb[i*settings->dim], (void *)gbest,sizeof(double) * settings->dim);
}
void IPSO_K::inform(int *comm, double *pos_nb, double *pos_b, double *fit_b,int improved, IPSO_K_settings_t * settings)
{
    int i, j;
    int b_n; 
    for (j=0; j<settings->size; j++) {
	b_n = j; 
	for (i=0; i<settings->size; i++)
	    if (comm[i*settings->size + j] && fit_b[i] < fit_b[b_n])
		b_n = i;
	memmove((void *)&pos_nb[j*settings->dim],
		(void *)&pos_b[b_n*settings->dim],
		sizeof(double) * settings->dim);
    }
}    
void IPSO_K::init_comm_ring(int *comm, IPSO_K_settings_t * settings) {
    int i;
    memset((void *)comm, 0, sizeof(int)*settings->size*settings->size);
    for (i=0; i<settings->size; i++) {
	comm[i*settings->size+i] = 1;
	if (i==0) {
	    comm[i*settings->size+i+1] = 1;
	    comm[(i+1)*settings->size-1] = 1;
	} else if (i==settings->size-1) {
	    comm[i*settings->size] = 1;
	    comm[i*settings->size+i-1] = 1;
	} else {
	    comm[i*settings->size+i+1] = 1;
	    comm[i*settings->size+i-1] = 1;
	}
    }
}

void IPSO_K::inform_ring(int *comm, double *pos_nb,double *pos_b, double *fit_b,double *gbest, int improved,IPSO_K_settings_t * settings)
{
    inform(comm, pos_nb, pos_b, fit_b, improved, settings);    
}
void IPSO_K::init_comm_random(int *comm, IPSO_K_settings_t * settings) {
    int i, j, k;
    memset((void *)comm, 0, sizeof(int)*settings->size*settings->size);
    for (i=0; i<settings->size; i++) {
	comm[i*settings->size + i] = 1;
	for (k=0; k<settings->nhood_size; k++) {
	    j = gsl_rng_uniform_int(settings->rng, settings->size);
	    comm[i*settings->size + j] = 1;
	}
    }
}
void IPSO_K::inform_random(int *comm, double *pos_nb,double *pos_b, double *fit_b,double *gbest, int improved,IPSO_K_settings_t * settings)
{
    if (!improved)
	init_comm_random(comm, settings);
    inform(comm, pos_nb, pos_b, fit_b, improved, settings);
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct { double x, y; int group; } point_t, *point;
 
double randf(double m)
{
	return m * rand() / (RAND_MAX - 1.);
}
 
point gen_xy(int count, double radius)
{
	double ang, r;
	point p, pt = malloc(sizeof(point_t) * count);
 
	/* note: this is not a uniform 2-d distribution */
	for (p = pt + count; p-- > pt;) {
		ang = randf(2 * M_PI);
		r = randf(radius);
		p->x = r * cos(ang);
		p->y = r * sin(ang);
	}
 
	return pt;
}
 
inline double dist2(point a, point b)
{
	double x = a->x - b->x, y = a->y - b->y;
	return x*x + y*y;
}
 
inline int
nearest(point pt, point cent, int n_cluster, double *d2)
{
	int i, min_i;
	point c;
	double d, min_d;
 
#	define for_n for (c = cent, i = 0; i < n_cluster; i++, c++)
	for_n {
		min_d = HUGE_VAL;
		min_i = pt->group;
		for_n {
			if (min_d > (d = dist2(c, pt))) {
				min_d = d; min_i = i;
			}
		}
	}
	if (d2) *d2 = min_d;
	return min_i;
}
 
void Kmeans(point pts, int len, point cent, int n_cent)
{
#	define for_len for (j = 0, p = pts; j < len; j++, p++)
	int i, j;
	int n_cluster;
	double sum, *d = malloc(sizeof(double) * len);
 
	point p, c;
	cent[0] = pts[ rand() % len ];
	for (n_cluster = 1; n_cluster < n_cent; n_cluster++) {
		sum = 0;
		for_len {
			nearest(p, cent, n_cluster, d + j);
			sum += d[j];
		}
		sum = randf(sum);
		for_len {
			if ((sum -= d[j]) > 0) continue;
			cent[n_cluster] = pts[j];
			break;
		}
	}
	for_len p->group = nearest(p, cent, n_cluster, 0);
	free(d);
}
 
point lloyd(point pts, int len, int n_cluster)
{
	int i, j, min_i;
	int changed;
 
	point cent = malloc(sizeof(point_t) * n_cluster), p, c;
 
	/* assign init grouping randomly */
	//for_len p->group = j % n_cluster;
 
	/* or call k++ init */
	Kmeans(pts, len, cent, n_cluster);
 
	do {
		/* group element for centroids are used as counters */
		for_n { c->group = 0; c->x = c->y = 0; }
		for_len {
			c = cent + p->group;
			c->group++;
			c->x += p->x; c->y += p->y;
		}
		for_n { c->x /= c->group; c->y /= c->group; }
 
		changed = 0;
		/* find closest centroid of each point */
		for_len {
			min_i = nearest(p, cent, n_cluster, 0);
			if (min_i != p->group) {
				changed++;
				p->group = min_i;
			}
		}
	} while (changed > (len >> 10)); /* stop when 99.9% of points are good */
 
	for_n { c->group = i; }
 
	return cent;
}
 
void print_eps(point pts, int len, point cent, int n_cluster)
{
#	define W 400
#	define H 400
	int i, j;
	point p, c;
	double min_x, max_x, min_y, max_y, scale, cx, cy;
	double *colors = malloc(sizeof(double) * n_cluster * 3);
 
	for_n {
		colors[3*i + 0] = (3 * (i + 1) % 11)/11.;
		colors[3*i + 1] = (7 * i % 11)/11.;
		colors[3*i + 2] = (9 * i % 11)/11.;
	}
 
	max_x = max_y = -(min_x = min_y = HUGE_VAL);
	for_len {
		if (max_x < p->x) max_x = p->x;
		if (min_x > p->x) min_x = p->x;
		if (max_y < p->y) max_y = p->y;
		if (min_y > p->y) min_y = p->y;
	}
	scale = W / (max_x - min_x);
	if (scale > H / (max_y - min_y)) scale = H / (max_y - min_y);
	cx = (max_x + min_x) / 2;
	cy = (max_y + min_y) / 2;
 
	printf("%%!PS-Adobe-3.0\n%%%%BoundingBox: -5 -5 %d %d\n", W + 10, H + 10);
	printf( "/l {rlineto} def /m {rmoveto} def\n"
		"/c { .25 sub exch .25 sub exch .5 0 360 arc fill } def\n"
		"/s { moveto -2 0 m 2 2 l 2 -2 l -2 -2 l closepath "
		"	gsave 1 setgray fill grestore gsave 3 setlinewidth"
		" 1 setgray stroke grestore 0 setgray stroke }def\n"
	);
	for_n {
		printf("%g %g %g setrgbcolor\n",
			colors[3*i], colors[3*i + 1], colors[3*i + 2]);
		for_len {
			if (p->group != i) continue;
			printf("%.3f %.3f c\n",
				(p->x - cx) * scale + W / 2,
				(p->y - cy) * scale + H / 2);
		}
		printf("\n0 setgray %g %g s\n",
			(c->x - cx) * scale + W / 2,
			(c->y - cy) * scale + H / 2);
	}
	printf("\n%%%%EOF");
	free(colors);
#	undef for_n
#	undef for_len
}
 
#define PTS 100000
#define K 11

void IPSO_K::IPSO_K_set_default_settings(IPSO_K_settings_t *settings) {
    settings->dim = 30;
    settings->x_lo = -20;
    settings->x_hi = 20;
    settings->goal = 1e-5;
    settings->size = IPSO_K_calc_swarm_size(settings->dim);
    settings->print_every = 1000;
    settings->steps = 100000;
    settings->c1 = 1.496;
    settings->c2 = 1.496;
    settings->w_max = IPSO_K_INERTIA;
    settings->w_min = 0.3;
    settings->clamp_pos = 1;
    settings->nhood_strategy = IPSO_K_NHOOD_RING;
    settings->nhood_size = 5;
    settings->w_strategy = IPSO_K_W_LIN_DEC;
    settings->rng = NULL;
    settings->seed = time(0);

int i;
	point v = gen_xy(PTS, 10);
	point c = lloyd(v, PTS, K);
	print_eps(v, PTS, c, K);


}
void IPSO_K::IPSO_K_solve(IPSO_K_obj_fun_t obj_fun, void *obj_fun_params,IPSO_K_result_t *solution, IPSO_K_settings_t *settings)
{
    int free_rng = 0;
    double pos[settings->size][settings->dim]; 
    double vel[settings->size][settings->dim]; 
    double pos_b[settings->size][settings->dim];
    double fit[settings->size]; 
    double fit_b[settings->size]; 
    double pos_nb[settings->size][settings->dim]; 
    int comm[settings->size][settings->size];
    int improved; 
    int i, d, step;
    double a, b; 
    double rho1, rho2; 
    double w; 
    void (*inform_fun)(); 
    double (*calc_inertia_fun)(); 
    if (! settings->rng) {
	gsl_rng_env_setup();
	settings->rng = gsl_rng_alloc(gsl_rng_default);
	gsl_rng_set(settings->rng, settings->seed);
	free_rng = 1;
    }
    switch (settings->nhood_strategy)
	{
	case IPSO_K_NHOOD_GLOBAL :
	    inform_fun = inform_global;
	    break;
	case IPSO_K_NHOOD_RING :
	    init_comm_ring((int *)comm, settings);
	    inform_fun = inform_ring;
	    break;
	case IPSO_K_NHOOD_RANDOM :
	    init_comm_random((int *)comm, settings);
	    inform_fun = inform_random;
	    break;
	}
    switch (settings->w_strategy)
	{
	case IPSO_K_W_LIN_DEC :
	    calc_inertia_fun = calc_inertia_lin_dec;
	    break;
	}
    solution->error = DBL_MAX;
    for (i=0; i<settings->size; i++) {
	for (d=0; d<settings->dim; d++) {
            a = settings->x_lo + (settings->x_hi - settings->x_lo) * \gsl_rng_uniform(settings->rng);
	    b = settings->x_lo + (settings->x_hi - settings->x_lo) *	\gsl_rng_uniform(settings->rng);
	    pos[i][d] = a;
	    pos_b[i][d] = a;
	    vel[i][d] = (a-b) / 2.;
	}
	fit[i] = obj_fun(pos[i], settings->dim, obj_fun_params);
	fit_b[i] = fit[i]; 
	if (fit[i] < solution->error) {
	    solution->error = fit[i];
	    memmove((void *)solution->gbest, (void *)&pos[i],sizeof(double) * settings->dim);
	}	
    }
    w = IPSO_K_INERTIA;
    for (step=0; step<settings->steps; step++) {
	settings->step = step;
	if (settings->w_strategy)
	    w = calc_inertia_fun(step, settings);
	if (solution->error <= settings->goal) {
	    if (settings->print_every)
		printf("Goal achieved @ step %d (error=%.3e) :-)\n", step, solution->error);
	    break;
	}
	inform_fun(comm, pos_nb, pos_b, fit_b, solution->gbest,improved, settings);
	improved = 0;
	for (i=0; i<settings->size; i++) {
	    for (d=0; d<settings->dim; d++) {
		rho1 = settings->c1 * gsl_rng_uniform(settings->rng);
		rho2 = settings->c2 * gsl_rng_uniform(settings->rng);
		vel[i][d] = w * vel[i][d] +	\
		    rho1 * (pos_b[i][d] - pos[i][d]) +	\
		    rho2 * (pos_nb[i][d] - pos[i][d]);
		pos[i][d] += vel[i][d];
		if (settings->clamp_pos) {
		    if (pos[i][d] < settings->x_lo) {
			pos[i][d] = settings->x_lo;
			vel[i][d] = 0;
		    } else if (pos[i][d] > settings->x_hi) {
			pos[i][d] = settings->x_hi;
			vel[i][d] = 0;
		    }
		} else {
		    if (pos[i][d] < settings->x_lo) {
			pos[i][d] = settings->x_hi - fmod(settings->x_lo - pos[i][d],settings->x_hi - settings->x_lo);
			vel[i][d] = 0;
		    } else if (pos[i][d] > settings->x_hi) {
			pos[i][d] = settings->x_lo + fmod(pos[i][d] - settings->x_hi,settings->x_hi - settings->x_lo);
			vel[i][d] = 0;			
		    }
		}
	    }
	    fit[i] = obj_fun(pos[i], settings->dim, obj_fun_params);
	    if (fit[i] < fit_b[i]) {
		fit_b[i] = fit[i];
		memmove((void *)&pos_b[i], (void *)&pos[i],sizeof(double) * settings->dim);
	    }
	    if (fit[i] < solution->error) {
		improved = 1;
		solution->error = fit[i];
		memmove((void *)solution->gbest, (void *)&pos[i],sizeof(double) * settings->dim);
	    }
	}
	if (settings->print_every && (step % settings->print_every == 0))
	    printf("Step %d (w=%.2f) :: min err=%.5e\n", step, w, solution->error);
	
    }
    if (free_rng)
	gsl_rng_free(settings->rng);
}
}
