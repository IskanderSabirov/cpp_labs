#include "io.h"
#include "max.h"
#include "doComputation.h"
#include <stdio.h>

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
  printf("\n");
  return 0;
}
