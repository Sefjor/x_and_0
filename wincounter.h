#ifndef WINCOUNTER_H
#define WINCOUNTER_H
#include "enum_class_stage.h"
#include <string>
class WinCounter
{
public:
  WinCounter();
  std::string Results();
  void Worker(Stage);
private:
  int x_wins {};
  int zero_wins {};
  int draws {};
};

#endif // WINCOUNTER_H
