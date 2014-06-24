#include<stdio.h>
#include<stdlib.h>

#include<CL/cl.h>
#include"clutil.h"
#define CPU 0
#define GPU 1
#define PLATFORM GPU

#define STR_LEN 32

int main(int argc, char *argv[]){
  int i;
  char *cl_src = read_cl_src("hello.world.cl");

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
  
  cl_mem buffer_msg;

  buffer_msg = clCreateBuffer(context,CL_MEM_WRITE_ONLY,STR_LEN,NULL,&status);

  cl_program program;
  program = clCreateProgramWithSource(context,1,(const char**)&cl_src,NULL,&status);
  status = clBuildProgram(program,n_devices,devices,NULL,NULL,NULL);

  cl_kernel kernel;
  kernel = clCreateKernel(program,"hello",&status);

  status = clSetKernelArg(kernel,0,sizeof(cl_mem),&buffer_msg);

  cl_event event;
  status = clEnqueueTask(cmd_queue, kernel, 0, NULL,&event);
  clWaitForEvents(1,&event);

  char msg[STR_LEN];
  status = clEnqueueReadBuffer(cmd_queue,buffer_msg,CL_TRUE,0,STR_LEN,msg,0,NULL,NULL);
  
  printf("%s\n",msg);

  cl_ulong tstart,tend;
  double total_time;
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(tstart),&tstart,NULL);
  clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(tend),&tend,NULL);
  total_time = tend-tstart;
  printf("Execution time in ms: %0.3f ms\n",(total_time/1000000.0));

  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(cmd_queue);
  clReleaseMemObject(buffer_msg);
  clReleaseContext(context);

  free(platforms);
  free(devices);

  return 0;
}
