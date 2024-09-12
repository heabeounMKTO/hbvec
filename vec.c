#include <math.h>
#include <stdint.h>
#include "vec.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>


/// SSE and SSE2 functions
#if defined(__SSE__) && defined (__SSE2__)
#include <xmmintrin.h>
#include <emmintrin.h>

void print_vec(Vec3 v) {
  if(v.vec3_t == 0) {
     float val[4];
    _mm_store_ps(val, v.vec3_f.data);
    printf("x: %f y: %f z: %f\n", val[0], val[1], val[2]);
  } 
  if(v.vec3_t == 1){
    printf("x: %f y: %f z: %f\n", v.vec3_d.x, v.vec3_d.y, v.vec3_d.z);
  }

}

Vec3 vec3_new(float x, float y, float z, int type) {
  Vec3 v;
  switch(type) {
    case 0:
      v.vec3_f.data = _mm_set_ps(0.0f, z,y,x);
      v.vec3_t = type;
      break;
    case 1:
      v.vec3_d.x = (double) x;
      v.vec3_d.y = (double) y; 
      v.vec3_d.z = (double) z;
      v.vec3_t = type;
      break;
    default:
      printf("received unsuppourted vector type!\n");
      abort();
  }
  return v;
}
#elif defined(__SSE__) && defined(__SSE2__) && defined(__AVX__) 
#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

void print_vec(Vec3 v) {
  if(v.vec3_t == 0) {
     float val[4];
    _mm_store_ps(val, v.vec3_f.data);
    printf("x: %f y: %f z: %f\n", val[0], val[1], val[2]);
  } 
  if(v.vec3_t == 1){
    printf("x: %f y: %f z: %f\n", v.vec3_d.x, v.vec3_d.y, v.vec3_d.z);
  }

}

Vec3 vec3_new(float x, float y, float z, int type) {
  Vec3 v;
  switch(type) {
    case 0:
      v.vec3_f.data = _mm_set_ps(0.0f, z,y,x);
      v.vec3_t = type;
      break;
    case 1:
      v.vec3_f.data = _mm256_set_ps(0.0f, z,y,x);
      v.vec3_t = type;
      break;
    default:
      printf("received unsuppourted vector type!\n");
      abort();
  }
  return v;
}

#endif
