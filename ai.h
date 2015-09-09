#ifndef AI_H
#define AI_H
#include <vector>
#include <QDebug>
#include "enum_class_stage.h"

class Ai
{
public:
  Ai();
  void input(int A[10], int turn);
  void gameOver(Stage);
private:

  std::vector<std::vector<unsigned int>> stack;
std::vector<std::vector<unsigned int>> Data;
};


#endif // AI_H
