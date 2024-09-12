#ifndef HB_VEC_H
#define HB_VEC_H

#include <stdio.h>
#include <math.h>


#if defined(__SSE__) && defined(__SSE2__)
#include <xmmintrin.h>
#include <emmintrin.h>
typedef struct {
  __m128 data;
} Vec3_f;


typedef struct {
  double x, y,z;
} Vec3_d; 


#elif defined(__SSE__) && defined(__SSE2__) && defined(__AVX__)

#include <xmmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>

typedef struct {
  __m128 data;
} Vec3_f;


typedef struct {
  __m256 data;
} Vec3_d; 

#else // vanilla scalar 

typedef struct  {
  float x,y,z;
} Vec3_f;

typedef struct {
  double x,y,z;
} Vec3_d;

#endif

// your everyday float32 vec

// f32 => type 0 , 
// f64 => type 1
typedef union {
  int vec3_t;
  Vec3_f vec3_f;
  Vec3_d vec3_d;
} Vec3;
void print_vec(Vec3 v);
Vec3 float2vec(float f);
Vec3 double2vec(double f);
Vec3 negate_vec3(Vec3 v);
Vec3 new_vec(double x, double y, double z);
Vec3 int2vec(int i);
Vec3 add_vec3(Vec3 v1, Vec3 v2);
Vec3 div_vec3(Vec3 v1, Vec3 v2);
Vec3 mul_vec3(Vec3 v1, Vec3 v2);
Vec3 sub_vec3(Vec3 v1, Vec3 v2);
Vec3 unit_vec(Vec3 v);
double dot(Vec3 v1, Vec3 v2);
double len_sq(Vec3 v);
double length(Vec3 v);
Vec3 random_in_unit_sphere();
Vec3 random_unit_vec3_sphere();
Vec3 random_on_hemisphere(Vec3 normal);
#endif
