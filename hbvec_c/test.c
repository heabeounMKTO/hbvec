#include <stdio.h>
#include "vec.h"

int main() {
  for (int i = 0; i < 20; i++) {
    Vec_d* v1 = vecd_random(990000);
    Vec_d* v2 = vecd_random(990000);
    v1 = vecd_scale(v1, 0.000001);
    double dot = vecd_length(v1); 
    double cosine = vecd_cosine_similarity(v1, v2);
    printf("length %f\n", dot);
  }
}