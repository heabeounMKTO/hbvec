#include "vec.h"
#include <stdint.h>

int main() {
  Vec3 test1 = vec3_new(3.0, 4.0, 40.1);
  Vec3 unit_vec_scalar1 = vec3_unit(test1);
  vec3_print(unit_vec_scalar1);

  Vec3_d test = vec3d_new(3.0, 4.0, 40.1);
  Vec3_d unit_vec_scalar = vec3d_unit(test);
  vec3d_print(unit_vec_scalar);
}
