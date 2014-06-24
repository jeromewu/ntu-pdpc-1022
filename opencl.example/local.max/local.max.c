#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<CL/cl.h>
#include"clutil.h"
#define CPU 0
#define GPU 1
#define PLATFORM GPU

int main(int argc, char *argv[]){
  int i,n,datasize;
  char *cl_src = read_cl_src("local.max.cl");

  FILE *fp = fopen(argv[1],"r");
  sscanf(argv[2],"%d",&n);
  n = pow(2,n);
  datasize = n*sizeof(int);

  int *array_in = (int*)malloc(datasize);
  int *array_out = (int*)malloc(datasize);
  
  fread(array_in,sizeof(int),n,fp);

  cl_int status;

  cl_uint n_platforms = 0;
  cl_platform_id *platforms = get_platforms(&n_platforms);
 
  cl_uint n_devices = 0;
  cl_device_id *devices = get_devices(&n_devices,platforms[PLATFORM]);

  print_devices_info(n_devices,devices);

  cl_context context;
  context = clCreateContext(NULL,n_devices,devices,NULL,NULL,&status);
  
  cl_command_queue cmd_queue;
  cmd_queue = clCreateCommandQueue(context,devices[0],CL_QUEUE_PROFILING_ENABLE,&status);
  clFinish(cmd_queue);
  
  cl_mem buffer_array_in, buffer_array_out,buffer_n;

  buffer_array_in = clCreateBuffer(context,CL_MEM_READ_ONLY,datasize,NULL,&status);
  buffer_array_out = clCreateBuffer(context,CL_MEM_WRITE_ONLY,datasize,NULL,&status);
  buffer_n = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);

  status = clEnqueueWriteBuffer(cmd_queue,buffer_array_in,CL_FALSE,0,datasize,array_in,0,NULL,NULL);
  status = clEnqueueWriteBuffer(cmd_queue,buffer_n,CL_FALSE,0,sizeof(int),&n,0,NULL,NULL);

  cl_program program;
  program = clCreateProgramWithSource(context,1,(const char**)&cl_src,NULL,&status);
  status = clBuildProgram(program,n_devices,devices,NULL,NULL,NULL);

  cl_kernel kernel;
  kernel = clCreateKernel(program,"local_max",&status);

  status = clSetKernelArg(kernel,0,sizeof(cl_mem),&buffer_array_in);
  status = clSetKernelArg(kernel,1,sizeof(cl_mem),&buffer_array_out);
  status = clSetKernelArg(kernel,2,sizeof(cl_mem),&buffer_n);

  size_t global_work_size = n;

  cl_event event;
  status = clEnqueueNDRangeKernel(cmd_queue,kernel,1,NULL,&global_work_size,NULL,0,NULL,&event);
  clWaitForEvents(1,&event);

  status = clEnqueueReadBuffer(cmd_queue,buffer_array_out,CL_TRUE,0,datasize,array_out,0,NULL,NULL);
 
  //print_array(array_in,n);
  //print_array(array_out,n);

  cl_ulong tstart,tend;
  double total_time;
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(tstart),&tstart,NULL);
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(tend),&tend,NULL);
  total_time = tend-tstart;
  printf("Execution time in ms: %0.3f ms\n",(total_time/1000000.0));

  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(cmd_queue);
  clReleaseMemObject(buffer_array_in);
  clReleaseMemObject(buffer_array_out);
  clReleaseContext(context);

  free(array_in);
  free(array_out);
  free(platforms);
  free(devices);

  return 0;
}
