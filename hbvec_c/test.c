#include <stdio.h>
#include "vec.h"




int main() {
  Vec_d* v1 = vecd_random(10000);
  Vec_d* v2 = vecd_random(10000);
  // Vec_d* unit_vec = vecd_unit(v1);
  Vec_d* _v = vecd_add(v1, v2);
  double lenght; 
  // vecd_length(v1, lenght);
  // vecd_dot(v1, v2 , lenght);
  Vec_d* add_ = vecd_add(v1, v2);
  vecd_dot(add_, v1, lenght);
  // vecd_print(add_);
  printf("length %f\n", lenght);
}
