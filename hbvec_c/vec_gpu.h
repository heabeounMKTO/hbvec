/// KDOUY AYEAS SAEY HEH
///
///
/// ANH THUNH HA
#ifndef HB_VEC_CUDA_H
#define HB_VEC_CUDA_H

#ifdef __cplusplus
extern "C" {
#endif // extern cpp start

typedef struct {
 double x,y,z;
} Vec3_d;
// #include "vec.h"

void vec3d_add_cuda(Vec3_d *v1, 
                    Vec3_d *v2, 
                    Vec3_d *result, 
                    int batch_size); 

#ifdef __cplusplus
}
#endif // extern cpp end
#endif //HB_VEC_CUDA_H
