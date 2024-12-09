#include <stdio.h>
#include "vec.h"

int main() {
    Vec_d* v1 = vecd_random(10);
    Vec_d* v2 = vecd_random(10);
    v1 = vecd_scale(v1, 0.0000014);
    v2 = vecd_scale(v2, 0.0000053);
  double cosine_sim = vecd_cosine_similarity(v1, v2);
    printf("vecd cosine_sim %f\n", cosine_sim);

    Vec3_d v3_1 = vec3d_new(1.0 ,2.0,30.0); 
    Vec3_d v3_2 = vec3d_new(1.0 ,5123.0,4550.0); 
    double cosine = vec3d_cosine_similarity(v3_1, v3_2); 
    printf("vec3d cosine_simiarlity %f\n", cosine);
}
