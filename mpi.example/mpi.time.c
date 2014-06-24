#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int myrank, nprocs;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if(myrank != 0){
    double start,end;
    start = MPI_Wtime();
    sleep(myrank);
    end = MPI_Wtime();
    printf("Elapsed time = %lf s\n",end-start);
  }else{
    printf("Master do nothing.\n");
  }
  MPI_Finalize();
  return 0;
}
