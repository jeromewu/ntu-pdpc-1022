#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//argv[1]: filename
//argv[2]: N of NxN matrix

int main(int argc,char *argv[]){
  int n,len;
  int i;
  FILE *fp = fopen(argv[1],"wb");

  printf("%d\n",sizeof(size_t));
  sscanf(argv[2],"%d",&n);
  n = pow(2,n);
  srand(time(NULL));
  for(i=0;i<n*n;i++){
    int digit = rand()%256;
    printf("%d ",digit);
    fwrite(&digit,sizeof(int),1,fp);
  }
  printf("\n");
  fclose(fp);
  return 0;
}
