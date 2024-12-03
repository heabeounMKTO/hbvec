#include <stdio.h>
#include "vec.h"




int main() {
  Vec_d* v1 = vecd_ones(1000);
  Vec_d* v2 = vecd_ones(1000);
  Vec_d* v3 = vecd_add(v1, v2);
  vecd_print(v3);
}
