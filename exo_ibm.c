# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// define constants
// max time step
int maxTs = 10;

// World's size
int S = 40;

// initial pop
int popInit = 10;

// birth probability
float pB = 0.1;

// death probability 
float pD = 0.1;

// maximal moving distance (could be a proportion of world's size)
int maxDist = 2;

int main(int argc, char const *argv[])
{
	/* // define constants
	// max time step
	int maxTs = argv[1];

	// World's size
	int S = argv[2];

	// initial pop
	int popInit = argv[3];

	// birth probability
	float pB = argv[4];

	// death probability 
	float pD = argv[5];

	// maximal moving distance (could be a proportion of world's size)
	int maxDist = argv[6]; */

	// define variables
	// horizontal position
	int x;

	// vertical position
	int y;

	// dead or alive
	int DoA;

	// random generator seed
	srand(time(NULL));

	// build the pop table
	// pointer to pointers
	double **pop_table;
 
 	// as many column as variables 
  	col_number = 3;
  
  	pop_table = malloc(popInit * sizeof(double *));
  	for(row = 0; row < popInit; ++row)
  	{
      	*(pop_table + row) = malloc(col_number * sizeof(double));
  	}
  	
  	// random values for the first two columns
  	for (int i = 0; i < 1; ++i)
  	{
  		for (int row = 0; row < popInit; ++row)
  		{
  			// generate a random number between 0 and S

  			// assign it
  			*(*(pop_table + i) + row) = 3;
  		}
  	}
  	
  	// every ind is alive at first
  	for(row = 0; row < popInit; ++row)
  	{
      	*(*(pop_table + 2) + row) = 1;
  	}

  	for(row = 0; row < popInit; row++){
    	for(col = 0; col < col_number; col++){
      		printf("%f\t", *(*(pop_table + row) + col) );
    	}
    	printf("\n");
  	}
  
  	for(row = 0; row < popInit; row++){
    	free(*(pop_table + row));
  	}
  	free(pop_table);

	return 0;
}

// generate a random number between 0 and 1
  			int r = rand();
  			float test = r/(RAND_MAX+1.0);