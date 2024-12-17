# hbvec
my vector library , becuase im not writing a new vector library every fukcign time i start a new project. 

# usage example
if somehow u want to use this library...
```c
#include "vec.h"

int main() {
  // vector creation
  Vec3 test_f64 = vec3_create_double(1.0, 2.0, 3.0);
  Vec3 test_f32 = vec3_create_float(1.0f, 2.0f, 3.0f);
  Vec3 test_i32 = vec3_create_int(188, 2, 3);
  Vec3 test_i16 = vec3_create_short(1, 4, 12);
  Vec3 test_from_number = vec3_from_number(20000);

  // creates a random vector with a 64-bit float 
  Vec3 random_vec = vec3_create_random(VEC3_DOUBLE, 23124); 

  // common vector operations
  // and many more..
  double dot_test = _vec3_f32_dot(&test_f32, &test_f64);
  Vec3 unit_vec = vec3_unit(&test_i32);
  Vec3 scale = vec3_scale(&test_f64, 2.0);
  Vec3 neg = vec3_negate(&test_f64);
  Vec3 mod = vec3_mod(&test_f64, &test_f64);
  double cs = vec3_cosine_similarity(&test_f64, &test_i32);
}
```

please link with libmath like so
```bash
gcc program.c -o program -lm
```
