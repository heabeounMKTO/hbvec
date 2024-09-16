#include "vec.h"
#include <stdio.h>
#include <CL/cl.h>

int main() {
  clDeviceSettings _a = get_opencl_devices();
  cl_int err = clGetPlatformIDs(1, &_a.platform_id, NULL);
  cl_context context = clCreateContext(NULL, 1, &_a.device_id, NULL, NULL, &err);

}
