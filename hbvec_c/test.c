#include <stdio.h>
#include "rand.h"
#include "vec.h"
#include <time.h>
#define BENCH_RUN 1000


void bench_vecadd(){
  mt19937_state state;
  manual_seed(&state, 12348);
  clock_t begin = clock();
  for (int i = 0; i < BENCH_RUN; i++) {
    Vec_d* v1 = vecd_random(20000, state);
    Vec_d* v2 = vecd_random(20000, state);
    Vec_d* add_shit = vecd_add(v1, v2);
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("bench_vecadd time: %f seconds\n", time_spent);
}


int main() {
  bench_vecadd();  
  return 0;
}
