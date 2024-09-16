/* gpu operations for hbvec yoo */
#include "vec.h"
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>


available_isa get_opencl_devices() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    available_isa _a = {.platforms=ret};
    return _a;
  
}
