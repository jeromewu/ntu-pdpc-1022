#include<stdio.h>
#include<string.h>
#include<mpi.h>

#define MPI_TAG_1 1
#define MPI_TAG_2 2

#define MAX_STR_LEN 64

int main(int argc, char *argv[]){
  MPI_Init(&argc,&argv);
  int comm_size;
  int my_rank;

  MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  if(my_rank != 0){
    char *msg_tag1 = "This is message from tag MPI_TAG_1";
    char *msg_tag2 = "This is message from tag MPI_TAG_2";
    MPI_Send(msg_tag1,strlen(msg_tag1)+1,MPI_CHAR,0,MPI_TAG_1,MPI_COMM_WORLD);
    MPI_Send(msg_tag2,strlen(msg_tag2)+1,MPI_CHAR,0,MPI_TAG_2,MPI_COMM_WORLD);
  }else{
    int i;
    char buf[MAX_STR_LEN];
    int count = 0;
    MPI_Status status;
    for(i=1;i<comm_size;i++){
      MPI_Recv(buf,MAX_STR_LEN,MPI_CHAR,i,MPI_TAG_1,MPI_COMM_WORLD,&status);
      printf("%s\n",buf);
      MPI_Get_count(&status,MPI_CHAR,&count);
      printf("Count of message: %d\n",count);
    }
  }

  MPI_Finalize();
  return 0;
}
