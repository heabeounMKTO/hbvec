#include <math.h>
#include <stdint.h>
#include "vec.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

void print_vec(Vec3 v) {
  if(v.vec3_t == 0) 
    printf("x: %f y: %f z: %f\n", v.vec3_f.x, v.vec3_f.y, v.vec3_f.z);
  if(v.vec3_t == 1)
    printf("x: %f y: %f z: %f\n", v.vec3_d.x, v.vec3_d.y, v.vec3_d.z);

}

/// SSE and SSE2 functions
#if defined(__SSE__) && defined (__SSE2__)
#include <xmmintrin.h>
#include <emmintrin.h>

Vec3 vec3_new(float x, float y, float z) {
}


#endif
