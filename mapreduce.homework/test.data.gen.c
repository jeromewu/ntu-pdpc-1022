#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//argv[1]: number of the files

int main(int argc, char *argv[]){
  srand(time(NULL));
  int i,n;

  sscanf(argv[1],"%d",&n);

  for(i=0;i<n;i++){
    printf("%d %s\n",rand(),tmpnam(NULL));
  }

  printf("%d\n",RAND_MAX);
}
