# include <stdio.h>
# include <stdlib.h>
# include <time.h>


/* function declaration */
void init_repro (int **tab_in, int pop_size);
void update_movement (int **tab_in, int pop_size, int maxDist, int S);
int update_death(int **tab_in, int pop_size, float pD);
int update_birth(int **tab_in, int pop_size, int pop_alive, float pB);
int** swap_tables (int **tab_in, int col_number, int pop_size, int pop_alive, int pop_new);
// void swap_ptrs (int **ptr1, int **ptr2);


/* main function */
int main(int argc, char const *argv[])
{
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
  int maxDist = 3;

  // four columns: x, y, DoA, and reproduction
  int col_number = 4;
  
  // declare tracked variables
  // population size tracker
  int pop_size;
  int pop_alive;
  int pop_new;

  // random generator seed
  srand(time(NULL)); 

  // build the initial pop table
  // pointer to pointers
  int **pop_table;
  
  // allocate memory
  // allocate first column
  pop_table = malloc(popInit * sizeof(int *));
  // allocate other columns to each row
  for(int row = 0; row < popInit; ++row)
  {
    *(pop_table + row) = malloc(col_number * sizeof(int));
  }

  // initialize pop_tab
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

  // initialize pop_size
  pop_size = popInit;

  // debug OK
  printf("pop init \nx\ty\tDoA\tRepro \n");
  for(int row = 0; row < popInit; row++)
  {
    for(int col = 0; col < col_number; ++col)
    {
      printf("%d\t", *(*(pop_table + row) + col) );
    }
    printf("\n");
  }
  printf("pop size is %d \n", pop_size);

  // for/while loop on time steps
  for (int t = 0; t < maxTs; ++t)
  {
    /* update successively pop_table with the functions */
    // initialize reproduction
    init_repro (pop_table, pop_size);

    // individuals move
    update_movement(pop_table, pop_size, maxDist, S);

    // // debug OK
    // printf("after movement \nx\ty\tDoA\tRepro\n");
    // for(int row = 0; row < pop_size; row++)
    // {
    //   for(int col = 0; col < col_number; ++col)
    //   {
    //     printf("%d\t", *(*(pop_table + row) + col) );
    //   }
    //   printf("\n");
    // } 
    // printf("pop size is %d \n", pop_size);

    // die
    pop_alive = update_death(pop_table, pop_size, pD);

    // // debug OK
    // printf("after selection \nx\ty\tDoA\tRepro\n");
    // for(int row = 0; row < pop_size; row++)
    // {
    //   for(int col = 0; col < col_number; ++col)
    //   {
    //     printf("%d\t", *(*(pop_table + row) + col) );
    //   }
    //   printf("\n");
    // }
    // printf("pop size is %d \n", pop_size);
    // printf("pop alive is %d \n", pop_alive); 

    // and survivors reproduce
    pop_new = update_birth(pop_table, pop_size, pop_alive, pB);

    // // debug OK
    // printf("after birth \nx\ty\tDoA\tRepro\n");
    // for(int row = 0; row < pop_size; row++)
    // {
    //   for(int col = 0; col < col_number; ++col)
    //   {
    //     printf("%d\t", *(*(pop_table + row) + col) );
    //   }
    //   printf("\n");
    // }
    // printf("pop size is %d \n", pop_size);
    // printf("pop alive is %d \n", pop_alive); 
    // printf("pop new is %d \n", pop_new);

    // change the content of pop_table
    pop_table = swap_tables(pop_table, col_number, pop_size, pop_alive, pop_new);
    
    // update popsize
    pop_size = pop_new; 

    // debug
    printf("pop at  the end of timestep #%d \nx\ty\tDoA\tRepro\n", t+1);
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

/* movement function */
void update_movement (int **tab_in, int pop_size, int maxDist, int S)
{
  // browse individuals
  for (int row = 0; row < pop_size; ++row)
  {
    // generate two random integer in [-maxDist ; maxDist]
    int r1 = rand() % (2 * maxDist) - maxDist;
    int r2 = rand() % (2 * maxDist) - maxDist;

    // update positions
    *(*(tab_in + row) + 0) += r1;
    *(*(tab_in + row) + 1) += r2;

    // check for world boundaries (reflective)
    if (*(*(tab_in + row) + 0) > S) 
      { *(*(tab_in + row) + 0) = S - ((*(*(tab_in + row) + 0)) - S);}
    if (*(*(tab_in + row) + 0) < 0) 
      { *(*(tab_in + row) + 0) *= -1;}
    if (*(*(tab_in + row) + 1) > S) 
      { *(*(tab_in + row) + 1) = S - ((*(*(tab_in + row) + 1)) - S);}
    if (*(*(tab_in + row) + 1) < 0) 
      { *(*(tab_in + row) + 1) *= -1;}
  }
}


/* death function */
// takes a table in and updates it
int update_death(int **tab_in, int pop_size, float pD)
{
  // local variables
  // count of deaths
  int death_count = 0;
  // new pop_size
  int res = 0;

  // while/for loop on individuals in pop_table
  for (int row = 0; row < pop_size; ++row)
  {
    // test for death
    // generate a random number between 0 and 1
    float r = rand() / (double)(RAND_MAX);

    // test
    if (r < pD)
    {
      *(*(tab_in + row) + 2) = 0;
      death_count += 1;
    }
  } 

  // update table size
  res = pop_size - death_count;

  return res;
}


/* birth function */
int update_birth(int **tab_in, int pop_size, int pop_alive, float pB)
{
  // local variables
  // count of births
  int birth_count = 0;
  // new pop_size
  int res;

  // while/for loop on individuals in pop_table
  for (int row = 0; row < pop_size; ++row)
  {
    // only living individuals reproduce
    if (*(*(tab_in + row) + 2) == 1)
    {
      // test for birth
      // generate a random number between 0 and 1
      float r = rand()/(double)(RAND_MAX);

      // test
      if (r < pB)
      {
        *(*(tab_in + row) + 3) = 1;
        birth_count += 1;
      }
    }
  } 

  // update pop_size
  res = pop_alive + birth_count;

  return res;
}


/* function updating pop table */
int** swap_tables (int **tab_in, int col_number, int pop_size, int pop_alive, int pop_new)
{
  // initialize returning pointer to pointers
  int **tab_out = NULL;

  // allocate mem to it
  tab_out = malloc(pop_new * sizeof(int *));
  for(int row = 0; row < pop_new; ++row)
  {
    *(tab_out + row) = malloc(col_number * sizeof(int));
  }

  // // debug OK
  // printf("fresh tab_out \nx\ty\tDoA\tRepro\n");
  // for(int row = 0; row < pop_new; row++)
  // {
  //   for(int col = 0; col < col_number; ++col)
  //   {
  //     printf("%d\t", *(*(tab_out + row) + col) );
  //   }
  //   printf("\n");
  // }

  // fill it with the right info
  // track the living and copy their values to the new table
  // trackers of the survivors and new born
  int i = 0;
  int j = 0;

  for (int row = 0; row < pop_size; ++row)
  {   
    // browse the living and store them in the temporary table
    if ((*(*(tab_in + row) + 2)) == 1 && i < pop_alive)  // 
    {
      // copy the survivor values to the temp table
      for (int col = 0; col < col_number; ++col)
      {
        *(*(tab_out + i) + col) = *(*(tab_in + row) + col);
      }
      
      // *(*(tab_out + i) + 1) = *(*(tab_in + row) + 1);
      // *(*(tab_out + i) + 2) = *(*(tab_in + row) + 2);

      // // reset repro to 0
      // *(*(tab_out + i) + 3) = 0;
  
      // if individual reproduced add its offspring to tab_out at its parent's coordinates
      if ((*(*(tab_in + row) + 3)) == 1) // && j > (pop_new - pop_alive)
      {
        // copy the parents coordinates to the temp table
        *(*(tab_out + (pop_alive + j)) + 0) = *(*(tab_in + row) + 0);
        *(*(tab_out + (pop_alive + j)) + 1) = *(*(tab_in + row) + 1);

        // offspring are alive and did not reproduced yet
        *(*(tab_out + (pop_alive + j)) + 2) = 1;
        *(*(tab_out + (pop_alive + j)) + 3) = 0;
        
        // increment j
        j += 1;
      }

      // increment i
      i += 1;
    }
  }

  // // debug OK
  // printf("tab_out \nx\ty\tDoA\tRepro\n");
  // for(int row = 0; row < pop_new; row++)
  // {
  //   for(int col = 0; col < col_number; ++col)
  //   {
  //     printf("%d\t", *(*(tab_out + row) + col) );
  //   }
  //   printf("\n");
  // }

  // free tab_in
  for(int row = 0; row < pop_size; ++row)
  {
    free(*(tab_in + row));
  }
  free(tab_in);

  return tab_out;
}

// function to reinitialise reproduction tracker at the begining of every iteration
void init_repro (int **tab_in, int pop_size)
{
  // browse lines and set the fourth column value to 0
  for(int row = 0; row < pop_size; ++row)
  {
    *(*(tab_in + row) + 3) = 0;
  }

}

// void swap_ptrs (int **ptr1, int **ptr2)
// {
//   int temp = **ptr1;
//   **ptr1 = **ptr2;
//   **ptr2 = temp;
// }
