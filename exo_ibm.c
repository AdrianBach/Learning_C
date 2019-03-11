# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// define constants
// max time step
int maxTs = 3;

// World's size
int S = 40;

// initial pop
int popInit = 10;

// birth probability
float pB = 0.1;

// death probability 
float pD = 0.1;

// maximal moving distance (could be a proportion of world's size)
int maxDist = 3;

// four column: x, y, DoA, and reproduction
int col_number = 4;

// declare tracked variables

// population size tracker
int pop_size;

// death function
// takes pop_table in and updates it
void update_death(int **tab_in)
{
  // local variables
  // count of births
  int death_count = 0;

  // pop_size tracker
  int pop_alive;

  // new table right sized
  // pointer to pointers
  int **tab_out;

  // while/for loop on individuals in pop_table
  for (int row = 0; row < pop_size; ++row)
  {
    // test for death
    // generate a random number between 0 and 1
    float r = rand() / (double)(RAND_MAX);
    // OK with (double) before 

    // // debug OK
    // printf("random number generated in update_death is %f \n", r);

    // test
    if (r < pD)
    {
      *(*(tab_in + row) + 2) = 0;
      death_count += 1;
    }
  }

  /* here could be introduced a break if death_count = 0: "don't even touch pop_table" */

  // debug OK
  printf("after selection \n");
  for(int row = 0; row < pop_size; row++)
  {
    for(int col = 0; col < col_number; ++col)
    {
      printf("%d\t", *(*(tab_in + row) + col) );
    }
    printf("\n");
  } 

  // new table size
  pop_alive = pop_size - death_count;

  // allocate memory to tab_out
  tab_out = malloc(pop_alive * sizeof(int *));
  for(int row = 0; row < pop_alive; ++row)
  {
    *(tab_out + row) = malloc(col_number * sizeof(int));
  }

  // debug OK
  printf("fresh tab_out\n");
  for(int row = 0; row < pop_alive; row++)
  {
    for(int col = 0; col < col_number; ++col)
    {
      printf("%d\t", *(*(tab_out + row) + col) );
    }
    printf("\n");
  } 

  // track the living and copy their values to the new table

  // need for a tracker of the new table's rows
  int i = 0; // rows

  for (int row = 0; row < pop_size; ++row)
  {   
    // browse the livings and store them in the new table
    if (*(*(tab_in + row) + 2) == 1 && i < pop_alive)
    {
      for (int col = 0; col < col_number; ++col)
      {
        // copy the survivor values to the new table
        *(*(tab_out + i) + col) = *(*(tab_in + row) + col);
      }

      // increment i
      i += 1;
    }
  }

  // debug OK
  printf("copy survivors from tab_in to tab_out \n");
  for(int row = 0; row < pop_alive; row++)
  {
    for(int col = 0; col < col_number; ++col)
    {
      printf("%d\t", *(*(tab_out + row) + col) );
    }
    printf("\n");
  } 

  // free the old table
  for(int row = 0; row < pop_size; ++row)
  {
    free(*(tab_in + row));
  }
  free(tab_in);

  // update pop_size
  pop_size = pop_alive;

  // now tab_out has to become the new pop_table
  // pointer to pointers
  int **pop_table;
  
  // allocate memory
  pop_table = malloc(pop_size * sizeof(int *));
  for(int row = 0; row < pop_size; ++row)
  {
      *(pop_table + row) = malloc(col_number * sizeof(int));
  }
  
  // copy the survivor values from tab_out
  for (int row = 0; row < pop_size; ++row)
  {   
    for(int col = 0; col < col_number; ++col)
      {
        *(*(pop_table + row) + col) = *(*(tab_out + row) + col);
      }
  }

  // debug OK
  printf("new pop_table \n");
  for(int row = 0; row < pop_size; row++)
  {
    for(int col = 0; col < col_number; ++col)
    {
      printf("%d\t", *(*(pop_table + row) + col) );
    }
    printf("\n");
  } 

  // free tab_out
  for(int row = 0; row < pop_size; ++row)
  {
    free(*(tab_out + row));
  }
  free(tab_out);

}

// birth function for the survivors
// takes pop_table in and updates it
void update_birth(int **tab_in)
{
  // local variables
  // count of births
  int birth_count = 0;

  // pop_size tracker
  int pop_new;

  // new table right sized
  // pointer to pointers
  int **tab_out;

  // while/for loop on individuals in pop_table
  for (int row = 0; row < pop_size; ++row)
  {
    // test for death
    // generate a random number between 0 and 1
    float r = rand()/(RAND_MAX);

    // test
    if (r < pB)
    {
      *(*(tab_in + row) + 3) = 1;
      birth_count += 1;
    }
  } 

    // update pop_size
    pop_new = pop_size + birth_count;
  
    // allocate memory to tab_out
    tab_out = malloc(pop_new * sizeof(int *));
    for(int row = 0; row < pop_new; ++row)
    {
      *(tab_out + row) = malloc(col_number * sizeof(int));
    }

    // debug
    for(int row = 0; row < pop_new; row++)
    {
      for(int col = 0; col < col_number; ++col)
      {
        printf("%d\t", *(*(tab_out + row) + col) );
      }
      printf("\n");
    } 

    /* browse individuals and copy their values to the new table
       if they reproduced, the new born have the same coordinates */

    // initialize a tracker for the individuals that reproduced (between 0 and birth_count not included)
    int k = 0;

    // browsing loop
    for (int row = 0; row < pop_size; ++row)
    {
      for (int col = 0; col < col_number; ++col)
      {
        *(*(tab_out + row) + col) = *(*(tab_in + row) + col);

        // if the individual reproduced
        if (*(*(tab_in + row) + 3) == 1 && k < birth_count)
        {
          // new born has the same x and y as parent
          if (col == 0 || col == 1) {*(*(tab_out + pop_size + k) + col) = *(*(tab_in + row) + col);}

          // is alive and has not reproduced yet
          if (col == 2) {*(*(tab_out + pop_size + k) + col) = 1;}
          if (col == 3) {*(*(tab_out + pop_size + k) + col) = 0;}

          // increment i
          k += 1;
        }
      }
    }

    // debug
    for(int row = 0; row < pop_new; row++)
    {
      for(int col = 0; col < col_number; ++col)
      {
        printf("%d\t", *(*(tab_out + row) + col) );
      }
      printf("\n");
    } 

    // free the old table
    for(int row = 0; row < pop_size; ++row)
    {
      free(*(tab_in + row));
    }
    free(tab_in);

    // update pop_size
    pop_size = pop_new;

    // build the new pop table
    // pointer to pointers
    int **pop_table;
  
    // allocate memory
    pop_table = malloc(pop_size * sizeof(int *));
    for(int row = 0; row < pop_size; ++row)
    {
        *(pop_table + row) = malloc(col_number * sizeof(int));
    }

}

void update_movement (int **tab_in)
{
  // browse individuals
  for (int row = 0; row < pop_size; ++row)
  {
    // generate two random integer in [-maxDist ; maxDist]
    int r1 = rand() % (2 * maxDist) - maxDist;
    int r2 = rand() % (2 * maxDist) - maxDist;
    // cool thing, genarates between 0 and 2*maxDist and then substract maxDist
    // so if the r > maxdist -> positif and conversely if r < maxdist

    // update positions
    *(*(tab_in + row) + 0) += r1;
    *(*(tab_in + row) + 1) += r2;

    // check for world boundaries
    if (*(*(tab_in + row) + 0) > S) { *(*(tab_in + row) + 0) = S - ((*(*(tab_in + row) + 0)) - S);}
    if (*(*(tab_in + row) + 0) < 0) { *(*(tab_in + row) + 0) *= -1;}
    if (*(*(tab_in + row) + 1) > S) { *(*(tab_in + row) + 1) = S - ((*(*(tab_in + row) + 1)) - S);}
    if (*(*(tab_in + row) + 1) < 0) { *(*(tab_in + row) + 1) *= -1;}
  }
}

int main(int argc, char const *argv[])
{
	/* 
  // define constants
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
	int maxDist = argv[6];

	// define variables
	int pop_size;
  */

	// random generator seed
	srand(time(NULL));

  // build the initial pop table
  // pointer to pointers
  int **pop_table;
  
	// allocate memory
  pop_table = malloc(popInit * sizeof(int *));
	for(int row = 0; row < popInit; ++row)
	{
    	*(pop_table + row) = malloc(col_number * sizeof(int));
	}

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

    // no one has reproduced yet
    *(*(pop_table + row) + 3) = 0;
	}

  // // debug OK
  // printf("pop init check \nx\ty\tDoA\tRepro \n");
  // for(int row = 0; row < popInit; row++)
  // {
  //   for(int col = 0; col < col_number; ++col)
  //   {
  //  		printf("%d\t", *(*(pop_table + row) + col) );
  //   }
  //   printf("\n");
  // }
  // printf("pop size is %d \n", pop_size);
  // printf("random number generator test: %d\n", rand());
  // Rk: randmax is a constant

  // initialize pop_size
  pop_size = popInit;

  // for/while loop on time steps
  for (int t = 0; t < maxTs; ++t)
  {
    /* update successively pop_table with the functions */

    // // individuals move
    // update_movement(pop_table);
    // // function OK, rand() OK, access to pop_table OK

    // die
    update_death(pop_table);

    // // and survivors reproduce
    // update_birth(pop_table);

    // debug
    printf("pop at timestep #%d \nx\ty\tDoA\tRepro\n", t+1);
    for(int row = 0; row < pop_size; row++)
    {
      for(int col = 0; col < col_number; ++col)
      {
        printf("%d\t", *(*(pop_table + row) + col) );
      }
      printf("\n");
    }
    printf("pop size is %d \n", pop_size);
  }

  // free memory
  for(int row = 0; row < pop_size; ++row)
  {
  	free(*(pop_table + row));
  }
  free(pop_table);

	return 0;
}