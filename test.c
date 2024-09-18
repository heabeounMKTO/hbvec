#include "vec.h"
#include <math.h>
#include <stdint.h>
#include <time.h>

#define LOOP_TIMES 1000000

float sc_length(float x, float y, float z) {
  float len_sq = (x * x) + (y * y) + (z * z);
  return sqrt(len_sq);
};

void seed_random() { srand((unsigned int)time(NULL)); }

float random_float() {
  uint32_t _r = ((uint32_t)rand()) | rand();
  return (float)_r / ((uint32_t)RAND_MAX | RAND_MAX);
}

int main() {
  seed_random();
  clock_t start_scalar, end_scalar;
  double scalar_time;
  clock_t start_sse, end_sse;
  double sse_time;

  // debug_vec();
  Vec3 v = vec3_new(0.312f, 12.03f, 2.03f);
  vec3_print(v);
  Vec3 v2 = vec3_from_float(4.0f);
  Vec3 mul_test = vec3_sub(v2, v);
  float dot_test = vec3_dot(v, v2);

  start_scalar = clock();
  for (int i = 0; i < LOOP_TIMES; i++) {
    float len_sc = sc_length(random_float(), random_float(), random_float());
  }
  end_scalar = clock();
  scalar_time = ((double)(end_scalar - start_scalar)) / CLOCKS_PER_SEC;
  printf("SCALAR TIME: %f seconds\n", scalar_time);

  start_sse = clock();
  for (int i = 0; i < LOOP_TIMES; i++) {
    float len_sc =
        vec3_length(vec3_new(random_float(), random_float(), random_float()));
  }
  end_sse = clock();
  sse_time = ((double)(end_sse - start_sse)) / CLOCKS_PER_SEC;

  printf("SIMD TIME: %f seconds\n", sse_time);

  Vec3_d vecd = vec3d_new(1.0, 2.0, 3.9);
  Vec3_d vecd2 = vec3d_new(2.0, 1.4, 0.9);
  vec3d_print(vec3d_add(vecd, vecd2));
  return 0;
}
