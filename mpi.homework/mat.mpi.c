#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<mpi.h>

int ntasks,nslave,n,len;
int average_part_size,last_part_size;
int *array;
int **ans;

void print(int *array,int size){
  int i;
  for(i=0;i<size;i++){
    printf("%d\n",array[i]);
  }
}

int mult(int *_array){
  int i,j,k;
  int sum = 0;
  for(i=0;i<len;i++){
    for(j=0;j<len;j++){
      for(k=0;k<len;k++){
        sum+=_array[i*len+k]*_array[k*len+j];
      }
    }
  }
  return sum;
}

void master(){
  int i;
  int *ret = (int*)malloc(sizeof(int)*last_part_size);

  ans = (int**)malloc(sizeof(int*)*nslave);
  for(i=0;i<nslave;i++){
    ans[i] = (int*)malloc(sizeof(int)*last_part_size);
  }

  for(i=0;i<nslave;i++){
    MPI_Status status;
    MPI_Recv(ret,last_part_size,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    memcpy(ans[status.MPI_SOURCE-1],ret,sizeof(int)*last_part_size);
  }
  for(i=0;i<nslave-1;i++){
    print(ans[i],average_part_size);
  }
  print(ans[i],last_part_size);
}

void slave(int rank){
  int i;
  int *ret = (int*)malloc(sizeof(int)*last_part_size);
  if(rank != nslave){
    for(i=0;i<average_part_size;i++){
      ret[i] = mult(array+(((rank-1)*average_part_size+i)*len*len));
    }
  }else{
    for(i=0;i<last_part_size;i++){
      ret[i] = mult(array+((rank-1)*average_part_size+i)*len*len);
    }
  }
  MPI_Send(ret,last_part_size,MPI_INT,0,0,MPI_COMM_WORLD);
}

int main(int argc,char *argv[]){
  MPI_Init(&argc,&argv);
  int i;
  int rank;
  FILE *fp = fopen(argv[1],"rb");
  sscanf(argv[2],"%d",&n);
  sscanf(argv[3],"%d",&len);
  n = pow(10,n);
  len = pow(10,len);

  array = (int*)malloc(n*len*len*sizeof(int));
  fread(array,sizeof(int),n*len*len,fp);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
  nslave = ntasks-1;
  last_part_size = n - n/(nslave)*(nslave-1);
  average_part_size = n/nslave;
  
  if(rank == 0){
    master();
  }else{
    slave(rank);
  }
  MPI_Finalize();
  return 0;
}
