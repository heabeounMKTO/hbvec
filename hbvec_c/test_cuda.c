#include <stdlib.h>
#include "vec.h"

#include "vec_gpu.h"

int main() {
  Vec3_d* v1 = (Vec3_d *) malloc(1000 * sizeof(Vec3_d));
  Vec3_d* v2 = (Vec3_d *) malloc(1000 * sizeof(Vec3_d));
  Vec3_d* result= (Vec3_d *) malloc(1000 * sizeof(Vec3_d));
  for (int i = 0; i  < 1000; i++) {
    v1[i] = vec3d_from_int(i);
    v2[i] = vec3d_from_int(i+2);
  }
  vec3d_add_gpu(v1, v2, result, 1000); 
}
