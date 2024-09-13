#include "vec.h"

int main() {
  debug_vec();  
  Vec3 fuck = vec3_new(1.0f, 2.0f, 3.0f);
  Vec3 fuck2 = vec3_new(2.0f,1.0f,4.0f);
  Vec3 fuck22 = vec3_from_int(20);
  vec3_print(vec3_add(vec3_negate(fuck), fuck22));
  vec3_print(vec3_mul(vec3_div(fuck, fuck22), fuck2));

  return 0;
}
