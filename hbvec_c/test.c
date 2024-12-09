#include <stdio.h>
#include "vec.h"




int main() {
  Vec_d* v1 = vecd_random(200000);
  Vec_d* v2 = vecd_random(200000);
  v1 = vecd_scale(v1, 0.000001);
  double dot = vecd_length(v1); 
  printf("length %f\n", dot);

  // Vec_d* unit_vec = vecd_unit(v1);
  // Vec_d* _v = vecd_add(v1, v2);
  // Vec_d* add_ = vecd_add(v1, v2);
  // double dot = vecd_dot(add_, v1);
  // Vec_d* unit = vecd_unit(v2);
}
