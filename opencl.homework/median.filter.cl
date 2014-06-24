__kernel void median_filter(__global int *array_in, __global int *array_out, __global int *n){
  int idx = get_global_id(0);
  int dim = *n;
  int i,j,wi,wj,ti,tj;
  i = idx/dim;
  j = idx%dim;
  
  int tmp[9];

  int tmp_cnt = 0;

  for(wi=-1;wi<=1;wi++){
    for(wj=-1;wj<=1;wj++){
      if(i+wi<0 || j+wj<0 || i+wi>=dim || j+wj>=dim){
        continue;
      }
      tmp[tmp_cnt++] = array_in[(i+wi)*dim+j+wj];
    }  
  }
  int median = 256;
  for(ti=0;ti<tmp_cnt/2+1;ti++){
    int median_idx;
    median = 256;
    for(tj=0;tj<tmp_cnt;tj++){
      if(tmp[tj]<median){
        median = tmp[tj];
        median_idx = tj;
      }
    }
    tmp[median_idx] = 256;
  }
  array_out[idx] = median;
}
