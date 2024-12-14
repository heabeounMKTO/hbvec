#include "vec.h"

int main() {
  Vec3 test_f64 = vec3_create_double(1.0, 2.0, 3.0);
  Vec3 test_f32 = vec3_create_float(1.0, 2.0, 3.0);
  Vec3 test_i32 = vec3_create_int(188, 2, 3);
  Vec3 test_i16 = vec3_create_short(1, 4, 12);
  Vec3 test_from_float = vec3_from_number(20000);
  double dot_test = _vec3_f32_dot(&test_f32, &test_f64);
  Vec3 unit_vec = vec3_unit(&test_i32);
  Vec3 scale = vec3_scale(&test_f64, 2.0);
  Vec3 neg = vec3_negate(&test_f64);
  Vec3 mod = vec3_mod(&test_f64, &test_f64);
  double cs = vec3_cosine_similarity(&test_f64, &test_i32);
  Vec3 refl = vec3_reflect(&test_f64, &test_f32);
  double lsq = vec3_lengthsq(&test_f64);
  Vec3 randomshit = vec3_create_random(VEC3_DOUBLE, 1234);
  Vec3 randomshort = vec3_create_random(VEC3_SHORT, 144234);
  Vec3 randomnrm = vec3_create_random_normalized(14423454);
  vec3_print(&neg);
  vec3_print(&mod);
  printf("RANDOM SHIT\n");
  vec3_print(&randomshit);
  vec3_print(&randomshort);
  vec3_print(&randomnrm);
  printf("coseinf %f\n", cs);
  printf("length_sq %f\n", lsq);
  printf("refl\n");
  vec3_print(&refl);
  // Vec3 cross_test = vec3_cross(&test_f64,&test_from_float);
  // vec3_print(&cross_test);
}
