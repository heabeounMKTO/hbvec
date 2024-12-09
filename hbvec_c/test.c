#include <stdio.h>
#include "vec.h"

int main() {
    Vec_d* v1 = vecd_random(500);
    Vec_d* v2 = vecd_random(500);
    v1 = vecd_scale(v1, 0.0000014);
    v2 = vecd_scale(v2, 0.0000053);
    double dot = vecd_dot(v1, v2); 
    double len1 = vecd_length(v1); 
    double len2 = vecd_length(v2); 
    // double cs;
    // vecd_cosine_similarity(v1, v2, cs);
    printf("dot %f\n", dot);
    printf("v1_l %f\n", len1);
    printf("v2_l %f\n", len2);
    printf("cosine_sim %f\n", (dot / (len1 * len2)));
    // vecd_print(v1);
    // vecd_print(v2);


    Vec3_d v3_1 = vec3d_new(1.0 ,2.0,30.0); 
    Vec3_d v3_2 = vec3d_new(1.0 ,5123.0,4550.0); 
    double cosine = vec3d_cosine_similarity(v3_1, v3_2); 
    printf("cosine_simiarlity %f\n", cosine);
}
