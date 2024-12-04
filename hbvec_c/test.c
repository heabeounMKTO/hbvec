#include <stdio.h>
#include "vec.h"




int main() {
  Vec_d* v1 = vecd_ones(10000);
  Vec_d* v2 = vecd_ones(10000);
  Vec_d* v3 = vecd_add(v1, v2);
  Vec_d* scale_1 = vecd_scale(v3, 4.3);
  double dot_prod;
  vecd_dot(v1, scale_1, dot_prod);
  // vecd_print(dot);
  printf("dot prod %f", dot_prod);
}
