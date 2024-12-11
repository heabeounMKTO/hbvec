#ifndef HB_VEC_CUDA_H
#define HB_VEC_CUDA_H
#include "vec.h"

void vec3d_add_gpu(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int batch_size); 

#endif
