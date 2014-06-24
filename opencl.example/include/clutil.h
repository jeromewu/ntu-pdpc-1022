#ifndef _CLUTIL_C_
#define _CLUTIL_C_

#include<CL/cl.h>

char* read_cl_src(char* filename);
cl_platform_id* get_platforms(cl_uint *n_platforms);
cl_device_id* get_devices(cl_uint *n_devices, cl_platform_id platform);
void print_devices_info(cl_uint n_devices, cl_device_id *devices);

void print_array(int *array, int size);
#endif //_CLUTIL_C_
