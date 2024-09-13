#include "vec.h"

int main() {
  debug_vec();  
  Vec3 fuck = vec3_new(0.312f, 12.03f, 2.03f);
  Vec3 fuck2 = vec3_new(2.0f,1.0f,4.0f);
  Vec3 fuck22 = vec3_from_int(20);
  float len_test = vec3_length(fuck);
  Vec3 unit = vec3_unit(fuck);
  printf("len: %f\n", len_test);
  vec3_print(unit);
  vec3_print(vec3_add(vec3_negate(fuck), fuck22));
  vec3_print(vec3_mul(vec3_div(fuck, fuck22), fuck2));

  return 0;
}
