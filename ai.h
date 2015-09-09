#ifndef AI_H
#define AI_H
#include <vector>
#include <QDebug>
#include "enum_class_stage.h"
#include <unordered_map>
#include <array>

class Ai
{
public:
  Ai(Stage);
  void input(int A[], int turn);
  void gameOver(Stage);
  void dataOut();
  int askAi(int A[]);
private:
  std::vector<std::vector<unsigned int>> stack;
  std::unordered_map<unsigned int,std::array<int,10>> Data;
  Stage winCondition;
  std::array<int,10> temp;

};


#endif // AI_H
