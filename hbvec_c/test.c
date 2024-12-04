#include <stdio.h>
#include "vec.h"




int main() {
  Vec_d* v1 = vecd_ones(10000);
  Vec_d* v2 = vecd_ones(10000);
  Vec_d* v3 = vecd_add(v1, v2);
  Vec_d* scale_1 = vecd_scale(v3, 4.3);
  vecd_print(scale_1);
}
