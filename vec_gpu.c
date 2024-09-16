/* gpu operations for hbvec yoo */
#include "vec.h"
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>


char* loadOpenCLKernel_from_path(const char* filename, size_t* source_size) {
  FILE* fp=fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "cannot load openCL kernel file!\n");
    exit(1);
  }
  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  rewind(fp);
  char* source_str = (char*)malloc(size + 1);
  source_str[size] = '\0';
  fread(source_str, 1, size, fp);
  fclose(fp);
  *source_size = size;
  return source_str;
}

clDeviceSettings get_opencl_devices() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    clDeviceSettings _a = {.platforms_count=ret_num_platforms,
                        .device_count=ret_num_devices,
                        .platform_id=platform_id,
                        .device_id=device_id
                        };
    return _a;
}

void print_cl_device_settings(clDeviceSettings device_settings) {
  printf("hbvec OpenCL settings\n");
  printf("platform_count: %i\ndevice_count: %i\nplatform_id: %i\ndevice_id: %i\n", device_settings.platforms_count, device_settings.device_count, device_settings.platform_id, device_settings.device_id);
}

