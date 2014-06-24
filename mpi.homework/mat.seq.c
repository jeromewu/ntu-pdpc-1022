#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int *array;
int n,len;

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

int main(int argc, char *argv[]){
  int i;
  FILE *fp = fopen(argv[1],"rb");
  sscanf(argv[2],"%d",&n);
  sscanf(argv[3],"%d",&len);
  n = pow(10,n);
  len = pow(10,len);

  array = (int*)malloc(sizeof(int)*n*len*len);
  fread(array,sizeof(int),n*len*len,fp);
  for(i=0;i<n;i++){
    printf("%d\n",mult(array+(i*len*len)));
  }
  return 0;
}
