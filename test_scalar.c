#include "vec.h"
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LOOP_TIMES 10000000

void seed_random() { srand((unsigned int)time(NULL)); }

double random_d() {
  uint64_t _r = ((uint64_t)rand()) | rand();
  return (double)_r / ((uint64_t)RAND_MAX | RAND_MAX);
}

int main() {
  seed_random();
  clock_t start_scalar, end_scalar;
  double scalar_time;
  
  start_scalar = clock();
  for (int i = 0; i < LOOP_TIMES; i++) {
    double dot_sc = vec3_length(vec3_new(random_d(), random_d(),random_d()));
  }
  end_scalar = clock();
  scalar_time = ((double)(end_scalar - start_scalar)) / CLOCKS_PER_SEC;
  printf("SCALAR TIME: %f seconds\n", scalar_time);
}
