#include "max.h"
#include "logDebug.h"

int doComputation(__attribute__((unused))int a,__attribute__((unused)) double b) {

  int c = max(3, 4);

  logDebug('d');

  return c;
}
