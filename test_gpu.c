#include "vec.h"
#include <stdio.h>


int main() {
  available_isa _a = get_opencl_devices();
  printf("detected GPUs (by index) %i\n", _a.platforms);
}
