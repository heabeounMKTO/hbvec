#include "vec.h"


int main() {
  debug_vec(); 
  Vec3 v = vec3_new(0.312f, 12.03f, 2.03f);
  vec3_print(v);
  Vec3 v2 = vec3_from_float(4.0f);
  Vec3 mul_test = vec3_sub(v2, v);
  float dot_test = vec3_dot(v, v2);
  float length = vec3_length(v);
  vec3_print(mul_test);
  printf("dot prod %f\n", dot_test);
  printf("length %f\n", length);
  return 0;
}







