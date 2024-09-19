#include "vec.h"
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LOOP_TIMES 1000000

void seed_random() { srand((unsigned int)time(NULL)); }

float random_d() {
  uint64_t _r = ((uint64_t)rand()) | rand();
  return (float)_r / ((uint64_t)RAND_MAX | RAND_MAX);
}

int main() {
  seed_random();
  clock_t start_scalar, end_scalar;
  float scalar_time;
  
  start_scalar = clock();
  for (int i = 0; i < LOOP_TIMES; i++) {
    float dot_sc = vec3d_dot(vec3d_new(random_d(), random_d(),random_d()), 
                              vec3d_new(random_d(), random_d(),random_d())
                              );
  }
  end_scalar = clock();
  scalar_time = ((float)(end_scalar - start_scalar)) / CLOCKS_PER_SEC;
  printf("SIMD TIME: %f seconds\n", scalar_time);
}
