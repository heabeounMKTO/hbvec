#ifndef HB_VEC_H
#define HB_VEC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>


#ifdef __cplusplus
extern "C" {
#endif


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



//// CONSTANTS /////////
///////////////////////


// common numbers
// thanks cycles engine
/* Division */
#ifndef M_PI_F
#  define M_PI_F (3.1415926535897932f) /* pi */
#endif
#ifndef M_PI_2_F
#  define M_PI_2_F (1.5707963267948966f) /* pi/2 */
#endif
#ifndef M_PI_4_F
#  define M_PI_4_F (0.7853981633974830f) /* pi/4 */
#endif
#ifndef M_1_PI_F
#  define M_1_PI_F (0.3183098861837067f) /* 1/pi */
#endif
#ifndef M_2_PI_F
#  define M_2_PI_F (0.6366197723675813f) /* 2/pi */
#endif
#ifndef M_1_2PI_F
#  define M_1_2PI_F (0.1591549430918953f) /* 1/(2*pi) */
#endif
#ifndef M_1_4PI_F
#  define M_1_4PI_F (0.0795774715459476f) /* 1/(4*pi) */
#endif
#ifndef M_SQRT_PI_8_F
#  define M_SQRT_PI_8_F (0.6266570686577501f) /* sqrt(pi/8) */
#endif
#ifndef M_LN_2PI_F
#  define M_LN_2PI_F (1.8378770664093454f) /* ln(2*pi) */
#endif

/* Multiplication */
#ifndef M_2PI_F
#  define M_2PI_F (6.2831853071795864f) /* 2*pi */
#endif
#ifndef M_4PI_F
#  define M_4PI_F (12.566370614359172f) /* 4*pi */
#endif
#ifndef M_PI_4F
#  define M_PI_4F 0.78539816339744830962f /* pi/4 */
#endif

/* Float sqrt variations */
#ifndef M_SQRT2_F
#  define M_SQRT2_F (1.4142135623730950f) /* sqrt(2) */
#endif
#ifndef M_CBRT2_F
#  define M_CBRT2_F 1.2599210498948732f /* cbrt(2) */
#endif
#ifndef M_SQRT1_2F
#  define M_SQRT1_2F 0.70710678118654752440f /* sqrt(1/2) */
#endif
#ifndef M_SQRT3_F
#  define M_SQRT3_F (1.7320508075688772f) /* sqrt(3) */
#endif
#ifndef M_LN2_F
#  define M_LN2_F (0.6931471805599453f) /* ln(2) */
#endif
#ifndef M_LN10_F
#  define M_LN10_F (2.3025850929940457f) /* ln(10) */
#endif



///////// RANDOM VALUE GENERATOR ///////////
///
/// https://github.com/karpathy/llm.c/blob/master/llmc/rand.h
///
///////////////////////////////////////////
#define MERSENNE_STATE_M 397u
#define MERSENNE_STATE_N 624u

#define LMASK 0x7ffffffful
#define UMASK 0x80000000ul

// Copyright(c) Makoto Matsumoto and Takuji Nishimura

// This implementation follows PyTorch so that we are numerically identical when
// running verification tests.

typedef struct {
  unsigned long long seed_;
  int left_;
  unsigned int next_;
  unsigned int state_[MERSENNE_STATE_N];
  unsigned int MATRIX_A[2];
} mt19937_state;

static inline void manual_seed(mt19937_state *state, unsigned int seed) {
  state->MATRIX_A[0] = 0x0u;
  state->MATRIX_A[1] = 0x9908b0df;
  state->state_[0] = seed & 0xffffffff;
  for (unsigned int j = 1; j < MERSENNE_STATE_N; j++) {
    state->state_[j] =
        1812433253 * (state->state_[j - 1] ^ (state->state_[j - 1] >> 30)) + j;
    state->state_[j] &= 0xffffffff;
  }
  state->left_ = 1;
  state->next_ = 0;
}

static inline void next_state(mt19937_state *state) {
  state->left_ = MERSENNE_STATE_N;
  state->next_ = 0;
  unsigned int y, j;
  for (j = 0; j < MERSENNE_STATE_N - MERSENNE_STATE_M; j++) {
    y = (state->state_[j] & UMASK) | (state->state_[j + 1] & LMASK);
    state->state_[j] = state->state_[j + MERSENNE_STATE_M] ^ (y >> 1) ^
                       state->MATRIX_A[y & 0x1];
  }
  for (; j < MERSENNE_STATE_N - 1; j++) {
    y = (state->state_[j] & UMASK) | (state->state_[j + 1] & LMASK);
    state->state_[j] =
        state->state_[j + (MERSENNE_STATE_M - MERSENNE_STATE_N)] ^ (y >> 1) ^
        state->MATRIX_A[y & 0x1];
  }
  y = (state->state_[MERSENNE_STATE_N - 1] & UMASK) |
      (state->state_[0] & LMASK);
  state->state_[MERSENNE_STATE_N - 1] =
      state->state_[MERSENNE_STATE_M - 1] ^ (y >> 1) ^ state->MATRIX_A[y & 0x1];
}

static inline unsigned int randint32(mt19937_state *state) {
  if (!state)
    return 0;
  if (state->MATRIX_A[0] != 0 || state->MATRIX_A[1] != 0x9908b0df)
    manual_seed(state, 5489); // auto-initialize
  if (--state->left_ <= 0) {
    next_state(state);
  }
  unsigned int y = state->state_[state->next_++];
  y ^= y >> 11;
  y ^= (y << 7) & 0x9d2c5680;
  y ^= (y << 15) & 0xefc60000;
  y ^= y >> 18;
  return y;
}

static inline unsigned long long randint64(mt19937_state *state) {
  return (((unsigned long long)(randint32(state)) << 32) | randint32(state));
}

static inline float randfloat32(mt19937_state *state) {
  return (randint32(state) & ((1ull << 24) - 1)) * (1.0f / (1ull << 24));
}

static inline double randfloat64(mt19937_state *state) {
  return (randint64(state) & ((1ull << 53) - 1)) * (1.0 / (1ull << 53));
}

static void uniform_(float *data, unsigned int numel, float from, float to,
                     mt19937_state *state) {
  for (unsigned int t = 0; t < numel; t++) {
    data[t] = randfloat32(state) * (to - from) + from;
  }
}

// Box-Muller transform: maps uniform random numbers to Gaussian distributed
// numbers https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
static void normal_fill_16(float *data, float mean, float std) {
#define EPSILONE 1e-12f
  for (unsigned int t = 0; t < 8; t++) {
    float u1 = 1 - data[t];
    float u2 = data[t + 8];
    float radius = sqrtf(-2 * logf(u1 + EPSILONE));
    float theta = (float)(2.0 * M_PI * u2);
    data[t] = (radius * cosf(theta) * std + mean);
    data[t + 8] = (radius * sinf(theta) * std + mean);
  }
}

static void normal_fill(float *data, unsigned int numel, float mean, float std,
                        mt19937_state *state) {
  for (unsigned int t = 0; t < numel; t++) {
    data[t] = randfloat32(state);
  }
  for (unsigned int i = 0; i < numel - 15; i += 16) {
    normal_fill_16(data + i, mean, std);
  }
  if (numel % 16 != 0) {
    // recompute the last 16 values
    data = data + numel - 16;
    for (unsigned int i = 0; i < 16; i++) {
      data[i] = randfloat32(state);
    }
    normal_fill_16(data, mean, std);
  }
}

static inline void normal_(float *data, unsigned int numel, float mean,
                           float std, mt19937_state *state) {
#define EPSILONE 1e-12f
  if (numel >= 16) {
    normal_fill(data, numel, mean, std, state);
  } else {
    double next_double_normal_sample =
        0.0; // make compiler warning happy, won't be used
    int has_next_double_normal_sample = 0;
    for (unsigned int t = 0; t < numel; t++) {
      if (has_next_double_normal_sample) {
        data[t] = (float)(next_double_normal_sample * std + mean);
        has_next_double_normal_sample = 0;
        continue;
      }
      // for numel < 16 we draw a double (float64)
      float u1 = (float)randfloat64(state);
      float u2 = (float)randfloat64(state);
      float radius = sqrtf(-2 * logf(1 - u2 + EPSILONE));
      float theta = (float)(2.0 * M_PI * u1);
      next_double_normal_sample = radius * sinf(theta);
      has_next_double_normal_sample = 1;
      data[t] = (radius * cosf(theta) * std + mean);
    }
  }
}

static inline void init_identity_permutation(int *data, int numel) {
  for (int i = 0; i < numel; i++) {
    data[i] = i;
  }
}

static inline void random_permutation(int *data, int numel,
                                      mt19937_state *state) {
  for (int i = numel - 1; i > 0; i--) {
    // pick an index j in [0, i] with equal probability
    int j = randint32(state) % (i + 1);
    // swap i <-> j
    int tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
  }
}
////////////////////////////
///////  RANDOM STATE
////////////////////////////



////////////////////////////////////////////
//// FAST and APPROXIMATE MATH /////////////
///////////////////////////////////////////
#ifdef HB_VEC_USE_FAST_MATH

static inline float madd(const float a, const float b , const float c) {
  return a * b + c;
}

/* Based on http://www.pouet.net/topic.php?which=9132&page=2 */
static inline float fast_acosf(float x) {
  const float f = fabsf(x);
  /* clamp and crush denormals. */
  const float m = (f < 1.0f) ? 1.0f - (1.0f - f) : 1.0f;
  const float a = sqrtf(1.0f - m) *
                  (1.5707963267f + m * (-0.213300989f + m * (0.077980478f + m * -0.02164095f)));
  return x < 0 ? M_PI_F - a : a;
}

/* http://mathforum.org/library/drmath/view/62672.html */
static inline float fast_atanf(float x)
{
  const float a = fabsf(x);
  const float k = a > 1.0f ? 1 / a : a;
  const float s = 1.0f - (1.0f - k); /* Crush denormals. */
  const float t = s * s;
  float r = s * madd(0.43157974f, t, 1.0f) / madd(madd(0.05831938f, t, 0.76443945f), t, 1.0f);
  if (a > 1.0f) {
    r = M_PI_2_F - r;
  }
  return copysignf(r, x);
}

#endif // HB_VEC_USE_FAST_MATH
/////////////////////////////
/////// utilities ///////////
////////////////////////////

// hbvec internal clamping , SHRT_MAXmacro 
#ifndef __HB_VEC_CLAMP__
  #define __HB_VEC_CLAMP__(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))
#endif





static inline void vec3_log(const char* log) {
  fprintf(stdout, log);
} 

static inline void vec3_err(const char* log) {
  fprintf(stderr,"^^^^^^^^^[hbvec_ERROR]: Vec3");
  fprintf(stderr, log);
  exit(EXIT_FAILURE);
} 

static inline bool vec3_dtype_eq(const Vec3* a , const Vec3* b) {
  return a->dtype == b->dtype;
}

/// returns a random double within the specified boundary
static inline double random_clamped(double min, double max, int seed) {
  mt19937_state state;
  manual_seed(&state, seed);
  return __HB_VEC_CLAMP__(randfloat64(&state), min, max);
} 


static inline void vec3_print(const Vec3* vec) 
{
    switch (vec->dtype) {
        case VEC3_FLOAT:
            printf("Vec3 (float): [%f, %f, %f]\n", 
                   vec->data.f32[0], vec->data.f32[1], vec->data.f32[2]);
            break;
        case VEC3_INT:
            printf("Vec3 (int): [%d, %d, %d]\n", 
                   vec->data.i32[0], vec->data.i32[1], vec->data.i32[2]);
            break;
        case VEC3_DOUBLE:
            printf("Vec3 (double): [%f, %f, %f]\n", 
                   vec->data.f64[0], vec->data.f64[1], vec->data.f64[2]);
            break;
        case VEC3_SHORT:
            printf("Vec3 (short): [%hd, %hd, %hd]\n",
                   vec->data.i16[0], vec->data.i16[1], vec->data.i16[2]);
            break;
    }
}

static inline double vec3x(const Vec3* v) {
  double res;
  switch (v->dtype) {
    case VEC3_DOUBLE:
      res = v->data.f64[0];
      break;
    case VEC3_FLOAT:
      res = (double) v->data.f32[0];
      break;
    case VEC3_INT:
      res = (double) v->data.i32[0];
      break;
    case VEC3_SHORT:
      res = (double) v->data.i16[0];
      break;
  }
  return res;
}

static inline double vec3y(const Vec3* v) {
  double res;
  switch (v->dtype) {
    case VEC3_DOUBLE:
      res = v->data.f64[1];
      break;
    case VEC3_FLOAT:
      res = (double) v->data.f32[1];
      break;
    case VEC3_INT:
      res = (double) v->data.i32[1];
      break;
    case VEC3_SHORT:
      res = (double) v->data.i16[1];
      break;
  }
  return res;
}

static inline double vec3z(const Vec3* v) {
  double res;
  switch (v->dtype) {
    case VEC3_DOUBLE:
      res = v->data.f64[2];
      break;
    case VEC3_FLOAT:
      res = (double) v->data.f32[2];
      break;
    case VEC3_INT:
      res = (double) v->data.i32[2];
      break;
    case VEC3_SHORT:
      res = (double) v->data.i16[2];
      break;
  }
  return res;
}



static inline void vec3_print_pair(const Vec3* a, const Vec3* b) {
  fprintf(stdout, "Vec3 a:\n");
  vec3_print(a);
  fprintf(stdout, "Vec3 b:\n");
  vec3_print(b);
}


////////////////////////////////////////
//////// VECTOR OPERATIONS /////////////
///////////////////////////////////////
/* individual opertaions for each dtype because later 
 * i will add simd / cuda and aint no way im going into that 
`case` `switch` bullshit brah */


////////////////////////////////////////
///////////// CREATE //////////////////
//////////////////////////////////////
/// TODO; probably pass mt19937_state for the rand fucntions instead ofa  `int seed`

static inline Vec3 vec3_create_short(float x, float y, float z) 
{
    Vec3 v;
    v.data.i16[0] = x;
    v.data.i16[1] = y;
    v.data.i16[2] = z;
    v.dtype = VEC3_SHORT;
    return v;
}

static inline Vec3 vec3_create_float(float x, float y, float z) 
{
    Vec3 v;
    v.data.f32[0] = x;
    v.data.f32[1] = y;
    v.data.f32[2] = z;
    v.dtype = VEC3_FLOAT;
    return v;
}

static inline Vec3 vec3_create_int(int x, int y, int z) 
{
    Vec3 v;
    v.data.i32[0] = x;
    v.data.i32[1] = y;
    v.data.i32[2] = z;
    v.dtype = VEC3_INT;
    return v;
}

static inline Vec3 vec3_create_double(double x, double y, double z) 
{
    Vec3 v;
    v.data.f64[0] = x;
    v.data.f64[1] = y;
    v.data.f64[2] = z;
    v.dtype = VEC3_DOUBLE;
    return v;
}

static inline Vec3 vec3_create_random(Vec3Dtype vec_dtype, int seed) {
  mt19937_state state;
  manual_seed(&state, seed);
  Vec3 vec;
  vec.dtype = vec_dtype;
  switch (vec_dtype) {
        case VEC3_FLOAT:
            vec.data.f32[0] = randfloat32(&state);
            vec.data.f32[1] = randfloat32(&state);
            vec.data.f32[2] = randfloat32(&state);
            break;
        case VEC3_DOUBLE:
            vec.data.f64[0] = randfloat64(&state);
            vec.data.f64[1] = randfloat64(&state);
            vec.data.f64[2] = randfloat64(&state);
            break;
        case VEC3_INT:
            vec.data.i32[0] = randint32(&state); // Scale to integer range
            vec.data.i32[1] = randint32(&state);
            vec.data.i32[2] = randint32(&state);
            break;
        case VEC3_SHORT:
            vec.data.i16[0] = __HB_VEC_CLAMP__((short) randint32(&state), SHRT_MIN, SHRT_MAX);             
      vec.data.i16[1] = __HB_VEC_CLAMP__((short) randint32(&state), SHRT_MIN, SHRT_MAX); 
            vec.data.i16[2] = __HB_VEC_CLAMP__((short) randint32(&state), SHRT_MIN, SHRT_MAX); 
            break;
  }
  return vec;
}


// creates random normalized unit vectors, between -1.0 and 1.0
// Vec3.dtype = VEC3_FLOAT
static inline Vec3 vec3_create_random_normalized(int seed) {
  Vec3 vec;
  vec.dtype = VEC3_FLOAT;
  vec.data.f32[0] = random_clamped(-1.0, 1.0 , seed);  
  vec.data.f32[1] = random_clamped(-1.0, 1.0 , seed);  
  vec.data.f32[2] = random_clamped(-1.0, 1.0 , seed);  
  return vec;
}



/// infers data type from input, 
///
/// there is no allocation for `short` by default 
///
/// due to it might overflow or some shit
static inline Vec3 vec3_from_number(double x) {
    Vec3 vec;
    if (x == (float)x) {
        //  number can be represented as a float
        vec.data.f32[0] = (float)x;
        vec.data.f32[1] = (float)x;
        vec.data.f32[2] = (float)x;
        vec.dtype = VEC3_FLOAT;
    } else if (x == (int)x) {
        // number can be represented as an int
        vec.data.i32[0] = (int)x;
        vec.data.i32[1] = (int)x;
        vec.data.i32[2] = (int)x;
        vec.dtype = VEC3_INT;
    } else {
        // default to double
        vec.data.f64[0] = x;
        vec.data.f64[1] = x;
        vec.data.f64[2] = x;
        vec.dtype = VEC3_DOUBLE;
    }
    
    return vec;
}




////////// CAST ////////////
///////////////////////////

/// casts vecs from one dtype to another
/// 
static inline Vec3 _vec3_cast(const Vec3 *v, Vec3Dtype target_type) {
    Vec3 result;
    result.dtype = target_type;
    switch (v->dtype) {
      case VEC3_FLOAT:
        switch (target_type) {
          case VEC3_FLOAT:
              result.data = v->data;
              result.dtype = v->dtype;
              break;
          case VEC3_DOUBLE:
              result.data.f64[0] = (double)v->data.f32[0];
              result.data.f64[1] = (double)v->data.f32[1];
              result.data.f64[2] = (double)v->data.f32[2];
              break;
          case VEC3_INT:
              result.data.i32[0] = (int)v->data.f32[0];
              result.data.i32[1] = (int)v->data.f32[1];
              result.data.i32[2] = (int)v->data.f32[2];
              break;
          case VEC3_SHORT:
              result.data.i16[0] = (short)v->data.f32[0];
              result.data.i16[1] = (short)v->data.f32[1];
              result.data.i16[2] = (short)v->data.f32[2];
              break;
          }
          break;

      case VEC3_DOUBLE:
        switch (target_type) {
            case VEC3_FLOAT:
                result.data.f32[0] = (float)v->data.f64[0];
                result.data.f32[1] = (float)v->data.f64[1];
                result.data.f32[2] = (float)v->data.f64[2];
                break;
            case VEC3_DOUBLE:
                result.data = v->data;
                result.dtype = v->dtype;
                break;
            case VEC3_INT:
                result.data.i32[0] = (int)v->data.f64[0];
                result.data.i32[1] = (int)v->data.f64[1];
                result.data.i32[2] = (int)v->data.f64[2];
                break;
            case VEC3_SHORT:
                result.data.i16[0] = (short)v->data.f64[0];
                result.data.i16[1] = (short)v->data.f64[1];
                result.data.i16[2] = (short)v->data.f64[2];
                break;
        }
        break;


      case VEC3_INT:
        switch (target_type) {
            case VEC3_FLOAT:
                result.data.f32[0] = (float)v->data.i32[0];
                result.data.f32[1] = (float)v->data.i32[1];
                result.data.f32[2] = (float)v->data.i32[2];
                break;
            case VEC3_DOUBLE:
                result.data.f64[0] = (double)v->data.i32[0];
                result.data.f64[1] = (double)v->data.i32[1];
                result.data.f64[2] = (double)v->data.i32[2];
                break;
            case VEC3_INT:
                result.data = v->data;
                result.dtype = v->dtype;
                break;
            case VEC3_SHORT:
                result.data.i16[0] = (short)v->data.i32[0];
                result.data.i16[1] = (short)v->data.i32[1];
                result.data.i16[2] = (short)v->data.i32[2];
                break;
        }
        break;

      case VEC3_SHORT:
        switch (target_type) {
            case VEC3_FLOAT:
                result.data.f32[0] = (float)v->data.i16[0];
                result.data.f32[1] = (float)v->data.i16[1];
                result.data.f32[2] = (float)v->data.i16[2];
                break;
            case VEC3_DOUBLE:
                result.data.f64[0] = (double)v->data.i16[0];
                result.data.f64[1] = (double)v->data.i16[1];
                result.data.f64[2] = (double)v->data.i16[2];
                break;
            case VEC3_INT:
                result.data.i16[0] = (short)v->data.i16[0];
                result.data.i16[1] = (short)v->data.i16[1];
                result.data.i16[2] = (short)v->data.i16[2];
                break;
            case VEC3_SHORT:
                result.data = v->data;
                result.dtype = v->dtype;
                break;
        }
        break;

    }
  return result;
} 




/////////////////ADD/////////////////
////////////////////////////////////


/// adds all elements in the vec3 and returns
static inline double vec3_sum(const Vec3 *a) {
  Vec3 _cast_sum =  _vec3_cast(a, VEC3_DOUBLE);
  return _cast_sum.data.f64[0] + _cast_sum.data.f64[1] + _cast_sum.data.f64[2];
}

// averages shit in the vec
static inline double vec3_avg(const Vec3 *a) {
  Vec3 _cast_sum =  _vec3_cast(a, VEC3_DOUBLE);
  return vec3_sum(&_cast_sum) / 3;
}


static inline Vec3 _vec3_f32_add(const Vec3* a, const Vec3* b) {
    //type check, cant be too sure these days!     
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_add!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;
    result.data.f32[0] = a->data.f32[0] + b->data.f32[0];
    result.data.f32[1] = a->data.f32[1] + b->data.f32[1];
    result.data.f32[2] = a->data.f32[2] + b->data.f32[2];
    return result;
}


static inline Vec3 _vec3_f64_add(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_add!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;
    result.data.f64[0] = a->data.f64[0] + b->data.f64[0];
    result.data.f64[1] = a->data.f64[1] + b->data.f64[1];
    result.data.f64[2] = a->data.f64[2] + b->data.f64[2];
    return result;
}


static inline Vec3 _vec3_i32_add(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_add!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_INT;
    result.data.i32[0] = a->data.i32[0] + b->data.i32[0];
    result.data.i32[1] = a->data.i32[1] + b->data.i32[1];
    result.data.i32[2] = a->data.i32[2] + b->data.i32[2];
    return result;
}


static inline Vec3 _vec3_i16_add(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_add!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;
    result.data.i16[0] = a->data.i16[0] + b->data.i16[0];
    result.data.i16[1] = a->data.i16[1] + b->data.i16[1];
    result.data.i16[2] = a->data.i16[2] + b->data.i16[2];
    return result;
}





////////////// SUBTRACT /////////
/////////////////////////////////

static inline Vec3 _vec3_f32_sub(const Vec3* a, const Vec3* b) {
    //type check, cant be too sure these days!     
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_sub!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;
    result.data.f32[0] = a->data.f32[0] - b->data.f32[0];
    result.data.f32[1] = a->data.f32[1] - b->data.f32[1];
    result.data.f32[2] = a->data.f32[2] - b->data.f32[2];
    return result;
}


static inline Vec3 _vec3_f64_sub(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_sub!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;
    result.data.f64[0] = a->data.f64[0] - b->data.f64[0];
    result.data.f64[1] = a->data.f64[1] - b->data.f64[1];
    result.data.f64[2] = a->data.f64[2] - b->data.f64[2];
    return result;
}


static inline Vec3 _vec3_i32_sub(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_sub!\n"); 
    } 
    Vec3 result;
  result.dtype = VEC3_INT;
    result.data.i32[0] = a->data.i32[0] - b->data.i32[0];
    result.data.i32[1] = a->data.i32[1] - b->data.i32[1];
    result.data.i32[2] = a->data.i32[2] - b->data.i32[2];
    return result;
}


static inline Vec3 _vec3_i16_sub(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_sub!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;
    result.data.i16[0] = a->data.i16[0] - b->data.i16[0];
    result.data.i16[1] = a->data.i16[1] - b->data.i16[1];
    result.data.i16[2] = a->data.i16[2] - b->data.i16[2];
    return result;
}




////////////// MULTIPLY //////////////////
/////////////////////////////////////////

static inline Vec3 _vec3_f32_mul(const Vec3* a, const Vec3* b) {
    //type check, cant be too sure these days!     
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;
    result.data.f32[0] = a->data.f32[0] * b->data.f32[0];
    result.data.f32[1] = a->data.f32[1] * b->data.f32[1];
    result.data.f32[2] = a->data.f32[2] * b->data.f32[2];
    return result;
}


static inline Vec3 _vec3_f64_mul(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;
    result.data.f64[0] = a->data.f64[0] * b->data.f64[0];
    result.data.f64[1] = a->data.f64[1] * b->data.f64[1];
    result.data.f64[2] = a->data.f64[2] * b->data.f64[2];
    return result;
}


static inline Vec3 _vec3_i32_mul(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
  result.dtype = VEC3_INT;
    result.data.i32[0] = a->data.i32[0] * b->data.i32[0];
    result.data.i32[1] = a->data.i32[1] * b->data.i32[1];
    result.data.i32[2] = a->data.i32[2] * b->data.i32[2];
    return result;
}


static inline Vec3 _vec3_i16_mul(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;
    result.data.i16[0] = a->data.i16[0] * b->data.i16[0];
    result.data.i16[1] = a->data.i16[1] * b->data.i16[1];
    result.data.i16[2] = a->data.i16[2] * b->data.i16[2];
    return result;
}

///////////// DIVIDE ////////////////
/////////////////////////////////////

static inline Vec3 _vec3_f32_div(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_div!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;

    // handle division by zero
    if (b->data.f32[0] != 0.0f) {
      result.data.f32[0] = a->data.f32[0] /  b->data.f32[0];
    } else {
      result.data.f32[0] = 0.0f;
    }    
    if (b->data.f32[1] != 0.0f) {
      result.data.f32[1] = a->data.f32[1] / b->data.f32[1];
    } else {
      result.data.f32[1] = 0.0f;
    }    
    if (b->data.f32[2] != 0.0f) {
      result.data.f32[2] = a->data.f32[2] / b->data.f32[2];
    } else {
      result.data.f32[2] = 0.0f;
    }    
    return result;
}

static inline Vec3 _vec3_f64_div(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;

    if (b->data.f64[0] != 0.0) {
      result.data.f64[0] = a->data.f64[0] / b->data.f64[0];
    } else {
      result.data.f64[0] = 0.0;
    }    

    if (b->data.f64[1] != 0.0) {
      result.data.f64[1] = a->data.f64[1] / b->data.f64[1];
    } else {
      result.data.f64[1] = 0.0;
    }    

    if (b->data.f64[2] != 0.0) {
      result.data.f64[2] = a->data.f64[2] / b->data.f64[2];
    } else {
      result.data.f64[2] = 0.0;
    }    

    return result;
}

static inline Vec3 _vec3_i32_div(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_INT;

    if (b->data.i32[0] != 0) {
      result.data.i32[0] = a->data.i32[0] / b->data.i32[0];
    } else {
       result.data.i32[0]  = 0;
    }    

    if (b->data.i32[1] != 0) {
      result.data.i32[1] = a->data.i32[1] / b->data.i32[1];
    } else {
       result.data.i32[1]  = 0;
    }    

    if (b->data.i32[2] != 0) {
      result.data.i32[2] = a->data.i32[2] / b->data.i32[2];
    } else {
       result.data.i32[2]  = 0;
    }    
    return result;
}


static inline Vec3 _vec3_i16_div(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;

    if (b->data.i16[0] != 0) {
      result.data.i16[0] = a->data.i16[0] / b->data.i16[0];
    } else {
       result.data.i16[0]  = 0;
    }    
    if (b->data.i16[1] != 0) {
      result.data.i16[1] = a->data.i16[1] / b->data.i16[1];
    } else {
       result.data.i16[1]  = 0;
    }    

    if (b->data.i16[2] != 0) {
      result.data.i16[2] = a->data.i16[2] / b->data.i16[2];
    } else {
       result.data.i16[2]  = 0;
    }    
    return result;
}


///// MODULO //////
//////////////////

static inline Vec3 _vec3_f64_mod(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;
    result.data.f64[0] = fmod(a->data.f64[0], b->data.f64[0]);
    result.data.f64[1] = fmod(a->data.f64[1], b->data.f64[1]);
    result.data.f64[2] = fmod(a->data.f64[2], b->data.f64[2]);
    return result;
}

static inline Vec3 _vec3_f32_mod(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;
    result.data.f32[0] = fmod(a->data.f32[0], b->data.f32[0]);
    result.data.f32[1] = fmod(a->data.f32[1], b->data.f32[1]);
    result.data.f32[2] = fmod(a->data.f32[2], b->data.f32[2]);
    return result;
}

static inline Vec3 _vec3_i32_mod(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_INT;
    result.data.i32[0] = fmod(a->data.i32[0], b->data.i32[0]);
    result.data.i32[1] = fmod(a->data.i32[1], b->data.i32[1]);
    result.data.i32[2] = fmod(a->data.i32[2], b->data.i32[2]);
    return result;
}

static inline Vec3 _vec3_i16_mod(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;
    result.data.i16[0] = fmod(a->data.i16[0], b->data.i16[0]);
    result.data.i16[1] = fmod(a->data.i16[1], b->data.i16[1]);
    result.data.i16[2] = fmod(a->data.i16[2], b->data.i16[2]);
    return result;
}


////////////// DOT PRODUCT/////////////////
//////////////////////////////////////////

/* vector are casted to the result data type */

static inline float _vec3_f32_dot(const Vec3* a, const Vec3* b) {
    Vec3 _cast_a = _vec3_cast(a, VEC3_FLOAT); 
    Vec3 _cast_b = _vec3_cast(b, VEC3_FLOAT); 
    return (_cast_a.data.f32[0] * _cast_b.data.f32[0]) +
             (_cast_a.data.f32[1] * _cast_b.data.f32[1]) +
             (_cast_a.data.f32[2] * _cast_b.data.f32[2]);
}

static inline double _vec3_f64_dot(const Vec3* a, const Vec3* b) {
    Vec3 _cast_a = _vec3_cast(a, VEC3_DOUBLE); 
    Vec3 _cast_b = _vec3_cast(b, VEC3_DOUBLE); 
    return (_cast_a.data.f64[0] * _cast_b.data.f64[0]) +
             (_cast_a.data.f64[1] * _cast_b.data.f64[1]) +
             (_cast_a.data.f64[2] * _cast_b.data.f64[2]);
}

//////////////// CROSS PRODUCT /////////////////
///////////////////////////////////////////////


static inline Vec3 _vec3_f32_cross(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_FLOAT;
    result.data.f32[0] = a->data.f32[1] * b->data.f32[2] - b->data.f32[2] * a->data.f32[1]; 
    result.data.f32[1] = a->data.f32[2] * b->data.f32[0] - b->data.f32[0] * a->data.f32[2]; 
    result.data.f32[2] = a->data.f32[0] * b->data.f32[1] - b->data.f32[1] * a->data.f32[0]; 
    return result;
}


static inline Vec3 _vec3_f64_cross(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_DOUBLE;
    result.data.f64[0] = a->data.f64[1] * b->data.f64[2] - b->data.f64[2] * a->data.f64[1]; 
    result.data.f64[1] = a->data.f64[2] * b->data.f64[0] - b->data.f64[0] * a->data.f64[2]; 
    result.data.f64[2] = a->data.f64[0] * b->data.f64[1] - b->data.f64[1] * a->data.f64[0]; 
    return result;
}


static inline Vec3 _vec3_i32_cross(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_INT;
    result.data.i32[0] = a->data.i32[1] * b->data.i32[2] - b->data.i32[2] * a->data.i32[1]; 
    result.data.i32[1] = a->data.i32[2] * b->data.i32[0] - b->data.i32[0] * a->data.i32[2]; 
    result.data.i32[2] = a->data.i32[0] * b->data.i32[1] - b->data.i32[1] * a->data.i32[0]; 
    return result;
}


static inline Vec3 _vec3_i16_cross(const Vec3* a, const Vec3* b) {
    if (!vec3_dtype_eq(a, b)) {
      vec3_print_pair(a,b);
      vec3_err("Type mismatch in vec3_mul!\n"); 
    } 
    Vec3 result;
    result.dtype = VEC3_SHORT;
    result.data.i16[0] = a->data.i16[1] * b->data.i16[2] - b->data.i16[2] * a->data.i16[1]; 
    result.data.i16[1] = a->data.i16[2] * b->data.i16[0] - b->data.i16[0] * a->data.i16[2]; 
    result.data.i16[2] = a->data.i16[0] * b->data.i16[1] - b->data.i16[1] * a->data.i16[0]; 
    return result;
}





///////////// PUBLIC vec3 FUNCTIONS///////////////
/////////////////////////////////////////////////


/// square root, returns in `VEC3_FLOAT`
static inline Vec3 vec3_sqrt(const Vec3 *a) {
  Vec3 vec = _vec3_cast(a, VEC3_FLOAT);
  vec.data.f32[0] = sqrtf(vec.data.f32[0]); 
  vec.data.f32[1] = sqrtf(vec.data.f32[1]); 
  vec.data.f32[2] = sqrtf(vec.data.f32[2]); 
  return vec; 
}

/// floor (rounds down), returns in `VEC3_FLOAT`
static inline Vec3 vec3_floor(const Vec3 *a) {
  Vec3 vec = _vec3_cast(a, VEC3_FLOAT);
  vec.data.f32[0] = floor(vec.data.f32[0]); 
  vec.data.f32[1] = floor(vec.data.f32[1]); 
  vec.data.f32[2] = floor(vec.data.f32[2]); 
  return vec; 
}

/// ceil (rounds up), returns in `VEC3_FLOAT`
static inline Vec3 vec3_ceil(const Vec3 *a) {
  Vec3 vec = _vec3_cast(a, VEC3_FLOAT);
  vec.data.f32[0] = ceil(vec.data.f32[0]); 
  vec.data.f32[1] = ceil(vec.data.f32[1]); 
  vec.data.f32[2] = ceil(vec.data.f32[2]); 
  return vec; 
}



static inline Vec3 vec3_add(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_add(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_add(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_add(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_add(a,b);
      break;
  }
  return result;
}

static inline Vec3 vec3_sub(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_sub(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_sub(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_sub(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_sub(a,b);
      break;
  }
  return result;
}



static inline Vec3 vec3_mul(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_mul(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_mul(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_mul(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_mul(a,b);
      break;
  }
  return result;
}

static inline Vec3 vec3_div(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_div(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_div(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_div(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_div(a,b);
      break;
  }
  return result;
}

static inline Vec3 vec3_cross(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_cross(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_cross(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_cross(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_cross(a,b);
      break;
  }
  return result;
}


static inline Vec3 vec3_mod(const Vec3 *a, const Vec3 *b) {
  Vec3 result;
  switch (a->dtype) {
    case VEC3_FLOAT:
      result = _vec3_f32_mod(a, b);
      break;
    case VEC3_DOUBLE:
      result = _vec3_f64_mod(a,b);
      break;
    case VEC3_INT:
      result = _vec3_i32_mod(a,b);
      break;
    case VEC3_SHORT:
      result = _vec3_i16_mod(a,b);
      break;
  }
  return result;
}


/// `factor` is casted to whatever the input vector `dtype` is
static inline Vec3 vec3_scale(const Vec3* a, float factor) {
  Vec3 _a = vec3_from_number(factor);
  _a = _vec3_cast(&_a , a->dtype);
  Vec3 result = vec3_mul(a, &_a);
  return result;
}

static inline Vec3 vec3_negate(const Vec3* a) {
  Vec3 neg = vec3_from_number(-1);
  neg = _vec3_cast(&neg, a->dtype);
  Vec3 result = vec3_mul(a, &neg);
  return result;
}

// casts input to float then clamps to fmin/fmax 
static inline float vec3_length(const Vec3 *a) {
  Vec3 _cast_input = _vec3_cast(a, VEC3_FLOAT); 
  return __HB_VEC_CLAMP__(sqrt(_vec3_f32_dot(&_cast_input, &_cast_input)), FLT_MIN, FLT_MAX);  
}

// cast to float , to avoid the bullshit of int overflows etc
static inline Vec3 vec3_unit(const Vec3 *a) {
  Vec3 _cast_input = _vec3_cast(a, VEC3_FLOAT); 
  float len = vec3_length(&_cast_input);
  Vec3 vlen = vec3_create_float(len, len, len);
  return vec3_div(&_cast_input, &vlen);
}

static inline double vec3_cosine_similarity(const Vec3 *a, const Vec3 *b) {
  Vec3 _cast_a =  _vec3_cast(a, VEC3_DOUBLE);
  Vec3 _cast_b = _vec3_cast(b, VEC3_DOUBLE);
  return _vec3_f64_dot(&_cast_a, &_cast_b) / (vec3_length(&_cast_a) * vec3_length(&_cast_b));
}


/// calculates reflection
static inline Vec3 vec3_reflect(const Vec3 *incident , const Vec3 *unit_normal) {
  Vec3 refl;
  refl.dtype = VEC3_FLOAT;
  Vec3 _cast_a =  _vec3_cast(incident, VEC3_FLOAT);
  Vec3 _cast_b = _vec3_cast(unit_normal, VEC3_FLOAT);
  double dp = _vec3_f32_dot(&_cast_a,&_cast_b);
  // fuck it
  refl.data.f32[0] = incident->data.f32[0] - 2.0f * unit_normal->data.f32[0] * dp; 
  refl.data.f32[1] = incident->data.f32[1] - 2.0f * unit_normal->data.f32[1] * dp; 
  refl.data.f32[2] = incident->data.f32[2] - 2.0f * unit_normal->data.f32[2] * dp; 
  refl = _vec3_cast(&refl, incident->dtype);
  return refl;
}


static inline Vec3 vec3_refract(const Vec3 *incident, const Vec3 *normal, const double eta) {
  Vec3 refr;
  Vec3 _cast_a =  _vec3_cast(incident, VEC3_FLOAT);
  Vec3 _cast_b = _vec3_cast(normal, VEC3_FLOAT);
  refr.dtype = VEC3_FLOAT;
  double dp = _vec3_f32_dot(&_cast_a,&_cast_b);
  float k = 1.0f - eta * eta * (1.0f - dp * dp);
  if (k < 0.0f) {
    return vec3_create_float(0.0f, 0.0f, 0.0f);
  } else {
    refr.data.f32[0] = eta * incident->data.f32[0] - (eta * dp + sqrt(k)) * normal->data.f32[0];
    refr.data.f32[1] = eta * incident->data.f32[1] - (eta * dp + sqrt(k)) * normal->data.f32[1];
    refr.data.f32[2] = eta * incident->data.f32[2] - (eta * dp + sqrt(k)) * normal->data.f32[2];
    refr = _vec3_cast(&refr, incident->dtype);
    return refr;
  }
} 

static inline double vec3_lengthsq(const Vec3* a) {
  Vec3 _a = vec3_mul(a, a);
  return vec3_sum(&_a);
}



#ifdef __cplusplus
}
#endif
#endif // HB_VEC_H end
