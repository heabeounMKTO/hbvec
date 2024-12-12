#ifndef HB_VEC_H
#define HB_VEC_H
#include "rand.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x, y, z;
} Vec3;

typedef struct {
  double x, y, z;
} Vec3_d;

/// we got that N length f64 vec's
typedef struct {
  int dimension;
  double *components;
} Vec_d;




// f32 opps
static inline Vec3 vec3_new(double x, float y, float z) {
  Vec3 v = {.x = x, .y = y, .z = z};
  return v;
}

static inline void vec3_print(Vec3 v) {
  printf("x: %f y: %f z: %f", v.x, v.y, v.z);
}

static inline double vec3_lengthsq(Vec3 v) {
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

static inline Vec3 vec3_from_double(float f) {
  Vec3 v = {f, f, f};
  return v;
}

static inline Vec3 vec3_from_int(int i) {
  Vec3 v = {(double)i, (float)i, (float)i};
  return v;
}

static inline Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
  return v;
}

static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z};
  return v;
}

static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x * v2.x, .y = v1.y * v2.y, .z = v1.z * v2.z};
  return v;
}

static inline Vec3 vec3_div(Vec3 v1, Vec3 v2) {
  Vec3 result;
  if (v2.x != 0.0f) {
    result.x = v1.x / v2.x;
  } else {
    result.x = 0.0f; // Handle division by zero as needed
  }
  if (v2.y != 0.0f) {
    result.y = v1.y / v2.y;
  } else {
    result.y = 0.0f; // Handle division by zero as needed
  }
  if (v2.z != 0.0f) {
    result.z = v1.z / v2.z;
  } else {
    result.z = 0.0f; // Handle division by zero as needed
  }
  return result;
}
static inline Vec3 vec3_negate(Vec3 v) {
  Vec3 neg = {-v.x, -v.y, -v.z};
  return neg;
}

static inline double vec3_dot(Vec3 v1, Vec3 v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

static inline Vec3 vec3_cross(Vec3 v1, Vec3 v2) {
  return (Vec3){.x = v1.y * v2.z - v1.z * v2.y,
                .y = v1.z * v2.x - v1.x * v2.z,
                .z = v1.x * v2.y - v1.y * v2.x};
}

static inline double vec3_length(Vec3 v) { return sqrt(vec3_dot(v, v)); }

static inline Vec3 vec3_unit(Vec3 v) {
  double len = vec3_length(v);
  Vec3 vec = {len, len, len};
  return vec3_div(v, vec);
}

static inline Vec3 vec3_scale(Vec3 v, double t) {
  return (Vec3){v.x * t, v.y * t, v.z * t};
}
static inline double vec3x(Vec3 v) { return v.x; }
static inline double vec3y(Vec3 v) { return v.y; }
static inline double vec3z(Vec3 v) { return v.z; }

static inline double vec3_cosine_similarity(Vec3 v1, Vec3 v2) {
  return vec3_dot(v1, v2) / (vec3_length(v1) * vec3_length(v2));
}


static inline Vec3_d vec3d_new(double x, double y, double z) {
  Vec3_d v = {x, y, z};
  return v;
}

static inline void vec3d_print(Vec3_d v) {
  printf("x: %f y: %f z: %f\n", v.x, v.y, v.z);
}

static inline Vec3_d vec3d_from_int(int i) {
  Vec3_d v = {(double)i, (double)i, (double)i};
  return v;
}


static inline Vec3_d vec3d_from_double(double f) {
  Vec3_d v = {f, f, f};
  return v;
}

#ifndef HBVEC_USE_CUDA

/// f64 opps
static inline Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
  return v;
}

static inline Vec3_d vec3d_cross(Vec3_d v1, Vec3_d v2) {
  return (Vec3_d){.x = v1.y * v2.z - v1.z * v2.y,
                  .y = v1.z * v2.x - v1.x * v2.z,
                  .z = v1.x * v2.y - v1.y * v2.x};
}


static inline Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z};
  return v;
}

static inline Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x * v2.x, .y = v1.y * v2.y, .z = v1.z * v2.z};
  return v;
}

static inline double vec3d_lengthsq(Vec3_d v) {
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

static inline Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2) {
  Vec3_d result;
  if (v2.x != 0.0f) {
    result.x = v1.x / v2.x;
  } else {
    result.x = 0.0f; // Handle division by zero as needed
  }
  if (v2.y != 0.0f) {
    result.y = v1.y / v2.y;
  } else {
    result.y = 0.0f; // Handle division by zero as needed
  }
  if (v2.z != 0.0f) {
    result.z = v1.z / v2.z;
  } else {
    result.z = 0.0f; // Handle division by zero as needed
  }
  return result;
}

static inline double vec3d_dot(Vec3_d v1, Vec3_d v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

static inline double vec3d_length(Vec3_d v) {
  double dot_v = vec3d_dot(v, v);
  return sqrt(dot_v);
}
static inline Vec3_d vec3d_negate(Vec3_d v) {
  Vec3_d neg = {-v.x, -v.y, -v.z};
  return neg;
}

static inline Vec3_d vec3d_scale(Vec3_d v, double t) {
  return (Vec3_d){v.x * t, v.y * t, v.z * t};
}

static inline Vec3_d vec3d_unit(Vec3_d v) {
  double len = vec3d_length(v);
  Vec3_d vec = {len, len, len};
  return vec3d_div(v, vec);
}
static inline Vec3_d vec3d_from_float(double input) {
  return (Vec3_d){.x = input, .y = input, .z = input};
}

static inline Vec3_d vec3d_reflect(Vec3_d v, Vec3_d n) {
  Vec3_d _a = vec3d_mul(
      vec3d_mul(vec3d_from_double(2.0), vec3d_from_float(vec3d_dot(v, n))), n);
  return vec3d_sub(v, _a);
}

static inline Vec3_d vec3d_refract(Vec3_d uv, Vec3_d n, double etai_over_etat) {
  double cos_theta = fmin(vec3d_dot(vec3d_negate(uv), n), 1.0);
  Vec3_d r_out_perp =
      vec3d_scale(vec3d_add(uv, vec3d_scale(n, cos_theta)), etai_over_etat);
  Vec3_d r_out_parallel =
      vec3d_scale(n, -sqrt(fabs(1.0 - vec3d_lengthsq(r_out_perp))));
  return vec3d_add(r_out_perp, r_out_parallel);
}

static inline double vec3d_x(Vec3_d v) { return v.x; }
static inline double vec3d_y(Vec3_d v) { return v.y; }
static inline double vec3d_z(Vec3_d v) { return v.z; }

static inline double vec3d_cosine_similarity(Vec3_d v1, Vec3_d v2) {
  return vec3d_dot(v1, v2) / (vec3d_length(v1) * vec3d_length(v2));
}


#else 
#include "vec_gpu.h"





#endif /// HBVEC_USE_CUDA Vec3_d






static inline Vec_d *vecd_new(int dimension) {
  Vec_d *vec = (Vec_d *)malloc(sizeof(Vec_d));
  if (vec == NULL) {
    fprintf(stderr, "memalloc failed for Vec_d!\n");
    return NULL;
  }
  vec->dimension = dimension;
  vec->components = (double *)calloc(dimension, sizeof(double));
  if (vec->components == NULL) {
    fprintf(stderr, "memalloc failed for Vec_d!\n");
    free(vec);
    return NULL;
  }
  return vec;
}

static inline void vecd_free(Vec_d *vec) {
  if (vec) {
    free(vec->components);
    free(vec);
  }
}
// sets shit @ index brah (im sleepy as of writing)
static inline int vecd_set(Vec_d *vec, int index, double value) {
  // we got bounds checking before gta6
  if (!vec || index < 0 || index >= vec->dimension) {
    fprintf(stderr, "Invalid ahh index brah\n");
    return -1;
  }
  vec->components[index] = value;
  return 0;
}

static inline double vecd_get(Vec_d *vec, int index) {
  // we got bounds checking before gta6 (2)
  if (!vec || index < 0 || index >= vec->dimension) {
    fprintf(stderr, "Invalid vector or index\n");
    return 0.0;
  }
  return vec->components[index];
}

static inline Vec_d *vecd_zeros(int dim) {
  Vec_d *vec = vecd_new(dim);
  for (int i = 0; i < dim; i++) {
    vec->components[i] = 0.0;
  }
  return vec;
}

static inline Vec_d *vecd_ones(int dim) {
  Vec_d *vec = vecd_new(dim);
  for (int i = 0; i < dim; i++) {
    vec->components[i] = 1.0;
  }
  return vec;
}

/// creates a vector from a single double
static inline Vec_d *vecd_from_double(int dim, double f) {
  Vec_d *vec = vecd_new(dim);
  for (int i = 0; i < dim; i++) {
    vec->components[i] = f;
  }
  return vec;
}

static inline void vecd_print(const Vec_d *vec) {
  if (!vec) {
    printf("Invalid vector\n");
    return;
  }

  printf("Vector (Dim %d): [", vec->dimension);
  for (int i = 0; i < vec->dimension; i++) {
    printf("%s%.2f", i > 0 ? ", " : "", vec->components[i]);
  }
  printf("]\n");
}

// cpu n dim vector ops

static inline Vec_d *vecd_add(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "Vectors must have same dimension for addition\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  if (!result)
    return NULL;

  for (int i = 0; i < v1->dimension; i++) {
    result->components[i] = v1->components[i] + v2->components[i];
  }
  return result;
}

static inline Vec_d *vecd_sub(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "Vectors must have same dimension for addition\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  if (!result)
    return NULL;

  for (int i = 0; i < v1->dimension; i++) {
    result->components[i] = v1->components[i] - v2->components[i];
  }

  return result;
}

static inline Vec_d *vecd_mul(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "Vectors must have same dimension for multiplication\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  if (!result)
    return NULL;

  for (int i = 0; i < v1->dimension; i++) {
    result->components[i] = v1->components[i] * v2->components[i];
  }

  return result;
}

static inline Vec_d *vecd_div(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "Vectors must have same dimension for multiplication\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  if (!result)
    return NULL;

  for (int i = 0; i < v1->dimension; i++) {
    if (v2->components[i] != 0.0) {

      result->components[i] = v1->components[i] / v2->components[i];
    } else {
      result->components[i] = 0.0;
    }
  }
  return result;
}

static inline Vec_d *vecd_scale(const Vec_d *v1, double scale) {
  if (!v1) {
    fprintf(stderr, "invalid vector to scale!\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  if (!result)
    return NULL;
  for (int i = 0; i < v1->dimension; i++) {
    result->components[i] = v1->components[i] * scale;
  }
  return result;
}

static inline Vec_d *vecd_negate(const Vec_d *v1) {
  if (!v1) {
    fprintf(stderr, "invalid vector to scale!\n");
    return NULL;
  }
  Vec_d *result = vecd_new(v1->dimension);
  for (int i = 0; i < v1->dimension; i++) {
    result->components[i] = v1->components[i] * -1.0;
  }
  return result;
}

static inline double vecd_dot(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "invalid vector to scale!\n");
    return -1;
  }
  double result;
  for (int i = 0; i < v1->dimension; i++) {
    result += (double)(v1->components[i] * v2->components[i]);
  }
  return result;
}

static inline double vecd_length(const Vec_d *v) {
  double result = sqrt(vecd_dot(v, v));
  return result;
}

static inline Vec_d *vecd_unit(Vec_d *v) {
  double len_res;
  double len = vecd_length(v);
  Vec_d *result = vecd_new(v->dimension);
  for (int i = 0; i < v->dimension; i++) {
    result->components[i] = 1.0 / v->components[i];
  }
  return result;
}

static inline double vecd_cosine_similarity(const Vec_d *v1, const Vec_d *v2) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
    fprintf(stderr, "Vectors must have same dimension for multiplication\n");
    return -1;
  }
  double result = vecd_dot(v1, v2) / (vecd_length(v1) * vecd_length(v2));
  return result;
}

static inline Vec_d *vecd_random(int vec_length, mt19937_state state) {
  // mt19937_state state;
  Vec_d *result = vecd_new(vec_length);
  for (int i = 0; i < result->dimension; i++) {
    result->components[i] = (double)randint32(&state);
  }
  return result;
}

#endif
