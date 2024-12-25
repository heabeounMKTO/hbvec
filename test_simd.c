#include <smmintrin.h>
#include <stdio.h>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>

typedef enum {
    VEC3_FLOAT,
    VEC3_INT,
    VEC3_DOUBLE,
    VEC3_SHORT // mostly used for RGB / small stuff  
} Vec3Dtype;

typedef struct {
    union {
        float f32[3];
        double f64[3];
        int i32[3];
        short i16[3];
    } data;
    Vec3Dtype dtype;
} Vec3;

typedef struct {
    union {
        __m128 f32;
        __m256d f64;
        __m128i i32;
        __m128i i16;
    } data;
    Vec3Dtype dtype;
} Vec3_simd;

Vec3_simd _vec3_cast_simd(const Vec3 *a)
{
  Vec3_simd result; 
  Vec3Dtype vec_dtype = a->dtype;
  switch(vec_dtype) {
    case VEC3_FLOAT:
      result.dtype = vec_dtype;
      result.data.f32 = _mm_set_ps(0.0f, a->data.f32[2], a->data.f32[1], a->data.f32[0]);
      break;
    case VEC3_DOUBLE:
      result.dtype = vec_dtype;
      result.data.f64 = _mm256_set_pd(0.0f, a->data.f64[2], a->data.f64[1], a->data.f64[0]);
      break;
    case VEC3_INT:
      result.dtype = vec_dtype;
      result.data.i32 = _mm_set_epi32(0.0f, a->data.i32[2], a->data.i32[1], a->data.i32[0]);
      break;
    case VEC3_SHORT:
      result.dtype = vec_dtype;
      result.data.i16 = _mm_set_epi32(0.0f, a->data.i16[2], a->data.i16[1], a->data.i16[0]);
      break;
  }
}


int main() {
  return 0; 
}
