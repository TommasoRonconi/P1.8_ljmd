#include<input.h>

int get_a_line(FILE *fp, char * buf)
{
    char tmp[BLEN], *ptr;
    int i = 0;
	
    /* read a line and cut of comments and blanks */
    if (fgets(tmp, BLEN, fp))
    {

        ptr = strchr(tmp, '#');
        if (ptr)
            *ptr = '\0';
        i = strlen(tmp);
        --i;
        while (isspace(tmp[i]))
        {
            tmp[i] = '\0';
            --i;
        }
        ptr = tmp;
        while (isspace(*ptr))
        {
            ++ptr;
        }
        i = strlen(ptr);
        strcpy(buf, tmp);
        return 0;
    }
    else
    {
        perror("problem reading input");
        return -1;
    }
    
}

/* static  */
int populate_data(FILE * fp, char (*line)[BLEN], char (*restfile)[BLEN],
		  char (*trajfile)[BLEN], char (*ergfile)[BLEN], mdsys_t * sys,
		   int * nprint)
{


  /* Read input file if I'm rank 0 */
  if ( sys->rank == 0 ) {
  
    // reads atom number from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->natoms = atoi(*line);
  
    // reads mass from fp and saves it in data_struct sys  
    if (get_a_line(fp, *line))
      return 1;
    sys->mass = atof(*line);
    
    // reads epsilon from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->epsilon = atof(*line);
    
    // reads sigma from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->sigma = atof(*line);
    
    // reads cut-off radius from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->rcut = atof(*line);
    
    // reads box-size from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->box = atof(*line);
    
    // reads path/to/restart-file from fp and saves it in output array of char 'restfile'
    if (get_a_line(fp, *restfile))
      return 1;
    
    // reads path/to/trajectories-file from fp and saves it in output array of char 'trajfile'
    if (get_a_line(fp, *trajfile))
      return 1;
    
    // reads path/to/energies-file from fp and saves it in output array of char 'ergfile'
    if (get_a_line(fp, *ergfile))
      return 1;
    
    // reads number of steps from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->nsteps = atoi(*line);
    
    // reads size of time step from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    sys->dt = atof(*line);
    
    // reads box-size from fp and saves it in data_struct sys
    if (get_a_line(fp, *line))
      return 1;
    *nprint=atoi(*line);
    
  } //endif ( sys->rank == 0 )

  /* Broadcasting from rank 0 to all what has been read */
  MPI_Bcast( &( sys->natoms ), 1, MPI_INT, 0, sys->comm );
  MPI_Bcast( &( sys->mass ), 1, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->epsilon ), 1, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->sigma ), 1, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->rcut ), 1, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->box ), 1, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->nsteps ), 1, MPI_INT, 0, sys->comm );
  MPI_Bcast( &( sys->dt ), 1, MPI_DOUBLE, 0, sys->comm );

  return 0;
  
}

int readRestart( mdsys_t * sys, char restfile[BLEN] )
{

  int i;

  /* Reads the input file if I'm rank 0 */
  if ( sys->rank == 0 ) {
    
    FILE * fp = fopen(restfile, "r");
    
    if (fp)
      {
	for (i = 0; i < sys->natoms; ++i)
	  {
	    if ( fscanf(fp, "%lf%lf%lf", sys->rx + i, sys->ry + i, sys->rz + i) < 1 ) {
	      perror("No input in file.");
	      return 1;
	    }
	  }
	for (i = 0; i < sys->natoms; ++i)
	  {
	    if ( fscanf(fp, "%lf%lf%lf", sys->vx + i, sys->vy + i, sys->vz + i) < 1 ) {
	      perror("No input in file.");
	      return 2;
	    }
	  }
	fclose(fp);
      }
    else
      {
	perror("cannot read restart file");
	return 3;
      }
  } //endif ( sys->rank == 0 )

  /* Broadcasting from rank 0 to all what has been read */
  MPI_Bcast( &( sys->rx ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->ry ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->rz ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->vx ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->vy ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( &( sys->vz ), sys->natoms, MPI_DOUBLE, 0, sys->comm );
  
  /* Common operation for all */
  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);
  
  return 0;
  
}
