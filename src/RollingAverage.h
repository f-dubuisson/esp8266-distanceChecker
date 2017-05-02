#ifndef ROLLING_AVERAGE_H
#define ROLLING_AVERAGE_H

class RollingAverage {
public:
  RollingAverage(int size);
  ~RollingAverage();

  void add(int value);
  int getAverage();

private:
  int* values;
  int size;
  int count;
};

# endif
