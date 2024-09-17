

#include "vec.h"
#include <math.h>
#include <stdint.h>
#include <time.h>



int main() {
  Vec3_d vecd = vec3d_new(-1.99, -4.003906,-2.000000);
  vec3d_print(vec3d_unit(vecd));
}
