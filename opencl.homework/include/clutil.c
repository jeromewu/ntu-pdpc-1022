#include<stdio.h>
#include<stdlib.h>
#include"clutil.h"
#define MAX_SRC_SIZE (0x100000)

char* read_cl_src(char* filename){
  char *cl_src;
  FILE *fp = fopen(filename,"r");
  cl_src = (char*)malloc(MAX_SRC_SIZE*sizeof(char));
  fread(cl_src,sizeof(char),MAX_SRC_SIZE,fp);
  fclose(fp);
  return cl_src;
}

cl_platform_id* get_platforms(cl_uint *n_platforms){
  cl_int status;
  status = clGetPlatformIDs(0, NULL, n_platforms);
  cl_platform_id *platforms = (cl_platform_id*)malloc((*n_platforms)*sizeof(cl_platform_id));
  status = clGetPlatformIDs(*n_platforms, platforms, NULL);
  return platforms;
}

cl_device_id* get_devices(cl_uint *n_devices, cl_platform_id platform){
  cl_int status;
  status = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,NULL,n_devices);
  cl_device_id *devices = (cl_device_id*)malloc((*n_devices)*sizeof(cl_device_id));
  status = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,(*n_devices),devices,NULL);
  return devices;
}

void print_devices_info(cl_uint n_devices, cl_device_id *devices){
  int i;
  char *value;
  size_t value_size;
  cl_uint max_compute_units;
  cl_int status;
  for(i=0;i<n_devices;i++){
    status = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,0,NULL,&value_size);
    value = (char*)malloc(value_size*sizeof(char));
    status = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,value_size,value,NULL);
    fprintf(stderr,"%d.1 Device: %s\n",i,value);

    status = clGetDeviceInfo(devices[i],CL_DEVICE_VERSION,0,NULL,&value_size);
    value = (char*)malloc(value_size*sizeof(char));
    status = clGetDeviceInfo(devices[i],CL_DEVICE_VERSION,value_size,value,NULL);
    fprintf(stderr,"%d.2 Hardware version: %s\n",i,value);

    status = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,0,NULL,&value_size);
    value = (char*)malloc(value_size*sizeof(char));
    status = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,value_size,value,NULL);
    fprintf(stderr,"%d.3 Software version: %s\n",i,value);

    status = clGetDeviceInfo(devices[i],CL_DEVICE_OPENCL_C_VERSION,0,NULL,&value_size);
    value = (char*)malloc(value_size*sizeof(char));
    status = clGetDeviceInfo(devices[i],CL_DEVICE_OPENCL_C_VERSION,value_size,value,NULL);
    fprintf(stderr,"%d.4 OpenCL C version: %s\n",i,value);

    status = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(max_compute_units),&max_compute_units,NULL);
    fprintf(stderr,"%d.5 Parallel compute units: %d\n",i,max_compute_units);

  }
}

void print_array(int *array, int size){
  int i,j;
  for(i=0;i<size;i++){
    if((i+1)%10==0)
      printf("\n");
    printf("%d ",array[i]);
  }
  printf("\n");
}
