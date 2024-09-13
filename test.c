#define RUAPU_IMPLEMENTATION
#include "ruapu.h"
#include <stdio.h>

int main() {
  ruapu_init();
  const char* const* suppourted = ruapu_rua();
  while(*suppourted) {
    printf("%s\n", *suppourted);
    suppourted++;
  }
  return 0;
}







