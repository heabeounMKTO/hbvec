#include <stdlib.h>
#include "vec_gpu.h"


int main() {
  int batch_size = 9000000;
  Vec3_d* v1 = (Vec3_d *) malloc(batch_size * sizeof(Vec3_d));
  Vec3_d* v2 = (Vec3_d *) malloc(batch_size * sizeof(Vec3_d));
  Vec3_d* result= (Vec3_d *) malloc(batch_size * sizeof(Vec3_d));
  Vec3_d* result2 = (Vec3_d *) malloc(batch_size * sizeof(Vec3_d));
  for (int i = 0; i  < batch_size; i++) {
    v1[i] = vec3d_from_int(i+20);
    v2[i] = vec3d_from_int(i+2);
  }
  // vec3d_add_cuda(v1, v2, result, batch_size); 
  vec3d_mul_cuda(v1, v2, result, batch_size); 
  vec3d_add_cuda(result, v2, result2, batch_size); 
  vec3d_print(*result2);
}
