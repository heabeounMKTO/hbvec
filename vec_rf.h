#ifndef HB_VEC_H
#define HB_VEC_H
#include "rand.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


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


/////// utilities ///////////
////////////////////////////


static inline void vec3_log(const char* log) {
  fprintf(stdout, log);
} 


static inline void vec3_err(const char* log) {
  fprintf(stdout, log);
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

////////// CAST ////////////
///////////////////////////

/// casts vecs from one dtype to another
static inline Vec3 vec3_cast(const Vec3 *v, Vec3Dtype target_type) {
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



////////////// DOT PRODUCT/////////////////
//////////////////////////////////////////

/* vector are casted to the result data type */

static inline float _vec3_f32_dot(const Vec3* a, const Vec3* b) {
    Vec3 _cast_a = vec3_cast(a, VEC3_FLOAT); 
    Vec3 _cast_b = vec3_cast(b, VEC3_FLOAT); 
    return (_cast_a.data.f32[0] * _cast_b.data.f32[0]) +
             (_cast_a.data.f32[1] * _cast_b.data.f32[1]) +
             (_cast_a.data.f32[2] * _cast_b.data.f32[2]);
}

static inline double _vec3_f64_dot(const Vec3* a, const Vec3* b) {
    Vec3 _cast_a = vec3_cast(a, VEC3_DOUBLE); 
    Vec3 _cast_b = vec3_cast(b, VEC3_DOUBLE); 
    return (_cast_a.data.f64[0] * _cast_b.data.f64[0]) +
             (_cast_a.data.f64[1] * _cast_b.data.f64[1]) +
             (_cast_a.data.f64[2] * _cast_b.data.f64[2]);
}



//////////////// CROSS PRODUCT /////////////////
///////////////////////////////////////////////




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




#ifdef __cplusplus
}
#endif

#endif
