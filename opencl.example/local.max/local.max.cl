__kernel void local_max(__global int *array_in, __global int *array_out, __global int *n){
  int idx = get_global_id(0);
  int i;
  array_out[idx] = 0;
  for(i=-2;i<=2;i++){
    if(idx+i < 0){
      continue;
    }
    else if(idx >= *n){
      continue;
    }
    if(array_in[idx+i] > array_out[idx]){
      array_out[idx] = array_in[idx+i];
    }
  }
}
