#include "vec.h"
#include <math.h>
#include <stdint.h>

int main() {
  debug_vec();
  Vec3 new_shit = vec3_new(0.0f,0.1f,0.23f);
  vec3_print(new_shit);
}
