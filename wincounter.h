#ifndef WINCOUNTER_H
#define WINCOUNTER_H
#include "enum_class_stage.h"
#include <string>
class WinCounter
{
public:
  WinCounter();
  std::string results();
  void worker(Stage);
private:
  int xWins {};
  int zeroWins {};
  int draws {};
};

#endif // WINCOUNTER_H
