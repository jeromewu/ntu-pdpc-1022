#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
  int myrank, nprocs;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if(myrank != 0){
    int local_data;
    MPI_Bcast(&local_data,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Slave %d: data=%d\n",myrank,local_data);
  }else{
    int data = 100;
    MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Master: data=%d\n",data);
  }

  MPI_Finalize();
  return 0;
}
