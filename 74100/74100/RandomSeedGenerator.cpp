#include "RandomSeedGenerator.h"

/**
RandomSeedGenerator::RandomSeedGenerator(){
	gsl_rng *cm_rng;
}
RandomSeedGenerator::~RandomSeedGenerator(){}

using namespace std;

gsl_rng *cm_rng;

double Rng(){
	return (gsl_rng_uniform_pos(cm_rng));
}

int RngInt(int nmax){
	return (gsl_rng_uniform_int(cm_rng, nmax));
}

void RngChooseInt(int *dest, int k, int * src, int n){
	//int control = 0;
	size_t size = sizeof(int);
	gsl_ran_choose(cm_rng, dest, (size_t)k, src, (size_t)n, size);
	gsl_ran_shuffle(cm_rng, dest, (size_t)k, size);
	return;
}

void RngINIT(){
	struct timeval a;
	struct timezone b;
	unsigned long int seed;

	gettimeofday(&a, &b);

	FILE*filein = fopen("seed.inp", "r");
	FILE*fileout = fopen("seed.out", "w");

	if (filein == NULL)
	{
		printf("#seed.inp not found. Creating a new seed...\n");
		seed = a.tv_usec;
		printf("# %ld\n", seed);
		cm_rng = gsl_rng_alloc(gsl_rng_mt19937); //Makoto
		gsl_rng_set(cm_rng, seed);
		fprintf(fileout, "%ld\n", seed);
		fclose(fileout);
	}
	else{
		printf("\n#reading seed.inp .\n");
		fscanf(filein, "%ld", &seed);
		fprintf(fileout, "%ld", seed);
		cm_rng = gsl_rng_alloc(gsl_rng_mt19937); //Makoto
		gsl_rng_set(cm_rng, seed);
		fclose(fileout);
		fclose(filein);
	}
	return;
}

void RngINIT_DEBUG(char*filename){
	struct timeval a;
	struct timezone b;
	unsigned long int seed;

	gettimeofday(&a, &b);
	char seedname[256];
	sprintf(seedname, "%s.seed.out", filename);
	FILE*filein = fopen("seed.inp", "r");
	FILE*fileout = fopen(seedname, "w");

	if (filein == NULL)
	{
		printf("#seed.inp not found. Creating a new seed...\n");
		seed = a.tv_usec;
		printf("# %ld\n", seed);
		cm_rng = gsl_rng_alloc(gsl_rng_mt19937); //Makoto                                                                                                              
		gsl_rng_set(cm_rng, seed);
		fprintf(fileout, "%ld", seed);
		printf("#seed: %ld\n", seed);
		fclose(fileout);
	}
	else{
		printf("\n#reading seed.inp .\n");
		fscanf(filein, "%ld", &seed);
		fprintf(fileout, "%ld", seed);
		cm_rng = gsl_rng_alloc(gsl_rng_mt19937); //Makoto                                                                                                              
		gsl_rng_set(cm_rng, seed);
		fclose(fileout);
		fclose(filein);
	}
	return;
}


int RngPermutation(int *p, int size){
	for (int i = 0; i<size; i++)
		p[i] = i;
	gsl_ran_shuffle(cm_rng, p, (size_t)size, sizeof(int));
}
//*/