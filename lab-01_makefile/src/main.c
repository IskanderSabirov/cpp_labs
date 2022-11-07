#include "logDebug.h"
#include "max.h"
#include "doComputation.h"

main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
}
