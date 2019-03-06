# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// define constants
// // max time step
// int maxTs = 10;

// World's size
int S = 40;

// initial pop
int popInit = 10;

// // birth probability
// float pB = 0.1;

// // death probability 
// float pD = 0.1;

// // maximal moving distance (could be a proportion of world's size)
// int maxDist = 2;

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

	// // define variables
	// // horizontal position
	// int x;

	// // vertical position
	// int y;

	// // dead or alive
	// int DoA;

	// random generator seed
	srand(time(NULL));

	// build the initial pop table
	// pointer to pointers
	int **pop_table;
 
 	// as many column as variables 
  int col_number = 3;
  
	// allocate memory
  pop_table = malloc(popInit * sizeof(int *));
	for(int row = 0; row < popInit; ++row)
	{
    	*(pop_table + row) = malloc(col_number * sizeof(int));
	}

	//for (int i = 0; i < 1; ++i)
	//{
		for (int row = 0; row < popInit; ++row)
		{   
      // random values for the first two columns
			// generate 2 random numbers between 0 and S included
      int r1 = rand() % (S+1);
      int r2 = rand() % (S+1);

			// assign it
			*(*(pop_table + row) + 0) = r1;
      *(*(pop_table + row) + 1) = r2;

      // every ind is alive at first
      *(*(pop_table + row) + 2) = 1;
		}
	//}

  // debug OK
  printf("pop init check \nx\ty\tDoA\t \n");
	for(int row = 0; row < popInit; row++)
  {
  	for(int col = 0; col < col_number; col++)
    {
  		printf("%d\t", *(*(pop_table + row) + col) );
  	}
	  printf("\n");
  }

  // birth function
  // takes pop_table in and returns a new version of it
  /* type of return */ update_birth (/* arguments ? */)
  {
    // while loop on individuals


    // test for birth
    // generate a random number between 0 and 1
    float test = rand()/(RAND_MAX+1.0);

    // test
    if (test > pB)
    {
      return(** pop_);
    }

    // allocate memory for a new line at the end of the table

    // assign same position and a 1 to the DoA column

    // update pop_table

    return(pop_table); 
  }

  // free memory in the end
  for(int row = 0; row < popInit; row++){
  	free(*(pop_table + row));
  }
  free(pop_table);

	return 0;
}

// // generate a random number between 0 and 1
// int r = rand();
// float test = r/(RAND_MAX+1.0);