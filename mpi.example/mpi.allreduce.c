#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
  int myrank, nprocs;
  int global_sum = 0;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if(myrank != 0){
    MPI_Allreduce(&myrank,&global_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    printf("Slave %d:Global sum: %d\n",myrank,global_sum);
  }else{
    MPI_Allreduce(&myrank,&global_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    printf("Master:Global sum: %d\n",global_sum);
  }

  MPI_Finalize();
  return 0;
}
