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

// death probability 
float pD = 0.1;

// // maximal moving distance (could be a proportion of world's size)
// int maxDist = 2;

// death function
// takes pop_table in and updates it
void update_death(int **tab_in)
{
  // count of the deaths
  int deaths = 0;

  // while/for loop on individuals in pop_table
  for (int row = 0; row < pop_size; ++row)
  {
    // test for death
    // generate a random number between 0 and 1
    float r = rand()/(RAND_MAX);

    // test
    if (r < pD)
    {
      *(*(tab_in + row) + 2) = 0;
      deaths += 1;
    }

    // update pop_size
    pop_alive = pop_size - deaths; 

    // create a new table with the right size
    // pointer to pointers
    int **tab_out;
  
    // allocate memory
    tab_out = malloc(pop_alive * sizeof(int *));
    for(int row = 0; row < pop_alive; ++row)
    {
      *(tab_out + row) = malloc(col_number * sizeof(int));
    }

    // track the living and copy their values to the new table
    for (int row = 0; row < popInit; ++row)
    {   
      // browse the livings and store them in the new table
      if (*(*(tab_in + row) + 2 == 1)
      {
        for (int col = 0; col < col_number; ++col)
        {
          *(*(tab_out + row) + col = *(*(tab_in + row) + col;
        }
      }
    }

    // free the old table
    for(int row = 0; row < pop_size; ++row)
    {
      free(*(tab_in + row));
    }
    free(tab_in);

    // rename the new table correctly ?

    //return(0); 
  }
}

// birth function for the survivors
// takes pop_table in and updates it
void update_birth(int **tab_in)
{
  /* code */  
}

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
  	for(int col = 0; col < col_number; ++col)
    {
  		printf("%d\t", *(*(pop_table + row) + col) );
  	}
	  printf("\n");
  }
  // printf("sizeof(pop_table) is %lu \n", sizeof(pop_table));
  // printf("sizeof(**pop_table) is %lu \n", sizeof(**pop_table));
  // printf("sizeof(*pop_table) is %lu \n", sizeof(*pop_table));
  // printf("sizeof(pop_table[0]) is %lu \n", sizeof(pop_table[0]));
  // printf("sizeof(pop_table[0][0]) is %lu \n", sizeof(pop_table[0][0]));

  // initiate a variable for the size of pop_table
  int pop_size = popInit;

  // for/while loop on time steps
  for (int t = 0; t < maxTs; ++t)
  {
    /* update successively pop_table with the functions */
  }

  // free memory in the end
  for(int row = 0; row < popInit; ++row){
  	free(*(pop_table + row));
  }
  free(pop_table);

	return 0;
}