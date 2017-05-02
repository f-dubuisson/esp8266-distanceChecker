#include <stdlib.h>
#include <cstring>
#include "RollingAverage.h"

RollingAverage::RollingAverage(int _size) {
  values = new int[_size];
  size = _size;
}

RollingAverage::~RollingAverage() {
  free(values);
}

void RollingAverage::add(int value) {
  if (count == size) {
    // Shift all elements left
    count --;
    memmove(values, values + sizeof(int), count * sizeof(int));
  }
  values[count] = value;
  count ++;
}

int RollingAverage::getAverage() {
  int sum = 0;
  for (int i=0; i<count; i++) {
    sum += values[i];
  }

  return sum / count;
}
