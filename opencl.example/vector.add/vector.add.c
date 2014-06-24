#include<stdio.h>
#include<stdlib.h>

#include<CL/cl.h>
#include"clutil.h"
#define CPU 0
#define GPU 1
#define PLATFORM CPU

int main(int argc, char *argv[]){
  int i;
  char *cl_src = read_cl_src("vector.add.cl");

  int *A = NULL;
  int *B = NULL;
  int *C = NULL;

  const int elements = 1024;
  size_t datasize = sizeof(int)*elements;

  A = (int*)malloc(datasize);
  B = (int*)malloc(datasize);
  C = (int*)malloc(datasize);

  for(i=0;i<elements;i++){
    A[i] = i;
    B[i] = i;
  }
  
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
  
  cl_mem buffer_A, buffer_B, buffer_C;

  buffer_A = clCreateBuffer(context,CL_MEM_READ_ONLY,datasize,NULL,&status);
  buffer_B = clCreateBuffer(context,CL_MEM_READ_ONLY,datasize,NULL,&status);
  buffer_C = clCreateBuffer(context,CL_MEM_WRITE_ONLY,datasize,NULL,&status);

  status = clEnqueueWriteBuffer(cmd_queue,buffer_A,CL_FALSE,0,datasize,A,0,NULL,NULL);
  status = clEnqueueWriteBuffer(cmd_queue,buffer_B,CL_FALSE,0,datasize,B,0,NULL,NULL);

  cl_program program;
  program = clCreateProgramWithSource(context,1,(const char**)&cl_src,NULL,&status);
  status = clBuildProgram(program,n_devices,devices,NULL,NULL,NULL);

  cl_kernel kernel;
  kernel = clCreateKernel(program,"vector_add",&status);

  status = clSetKernelArg(kernel,0,sizeof(cl_mem),&buffer_A);
  status = clSetKernelArg(kernel,1,sizeof(cl_mem),&buffer_B);
  status = clSetKernelArg(kernel,2,sizeof(cl_mem),&buffer_C);

  size_t global_work_size = elements;

  cl_event event;
  status = clEnqueueNDRangeKernel(cmd_queue,kernel,1,NULL,&global_work_size,NULL,0,NULL,&event);
  clWaitForEvents(1,&event);

  status = clEnqueueReadBuffer(cmd_queue,buffer_C,CL_TRUE,0,datasize,C,0,NULL,NULL);
  
  print_array(C,elements);

  cl_ulong tstart,tend;
  double total_time;
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(tstart),&tstart,NULL);
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(tend),&tend,NULL);
  total_time = tend-tstart;
  printf("Execution time in ms: %0.3f ms\n",(total_time/1000000.0));

  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(cmd_queue);
  clReleaseMemObject(buffer_A);
  clReleaseMemObject(buffer_B);
  clReleaseMemObject(buffer_C);
  clReleaseContext(context);

  free(A);
  free(B);
  free(C);
  free(platforms);
  free(devices);

  return 0;
}
