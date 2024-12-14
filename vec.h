#ifndef HB_VEC_H
#define HB_VEC_H
#include "rand.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>


#ifdef __cplusplus
extern "C" {
#endif

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


/////// utilities ///////////
////////////////////////////

// hbvec internal clamping macro 
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


//////// VECTOR OPERATIONS /////////////
///////////////////////////////////////
/* individual opertaions for each dtype because later 
 * i will add simd / cuda and aint no way im going into that 
`case` `switch` bullshit brah */


///////////// CREATE //////////////////
//////////////////////////////////////
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
/* 
 * there is no automatic type casting for vector arithemetic 
all conversions must be explicit! 
 *
*/

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
