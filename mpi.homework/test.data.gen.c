#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//argv[1]: filename
//argv[2]: # of matrix
//argv[3]: N of NxN matrix

int main(int argc,char *argv[]){
  int n,len;
  int i,j;
  FILE *fp = fopen(argv[1],"wb");

  sscanf(argv[2],"%d",&n);
  sscanf(argv[3],"%d",&len);
  n = pow(10,n);
  len = pow(10,len);
  srand(time(NULL));
  for(i=0;i<n;i++){
    for(j=0;j<len*len;j++){
      int digit = (int)(pow(-1,rand())*rand())%2;
      fwrite(&digit,sizeof(int),1,fp);
    }
  }
  fclose(fp);
  return 0;
}
