#include <stdlib.h>
#include "RollingAverage.h"

RollingAverage::RollingAverage(int _size) {
  values = new int[_size];
  size = _size;
  start = 0;
}

RollingAverage::~RollingAverage() {
  free(values);
}

void RollingAverage::add(int value) {
  if (count < size) {
    values[count] = value;
    count ++;
  } else {
    start = (start+1) % size;
    values[(start+count) % size] = value;
  }
}

int RollingAverage::getAverage() {
  int sum = 0;
  for (int i=0; i<count; i++) {
    sum += values[i];
  }

  return sum / count;
}
