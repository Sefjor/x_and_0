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
  void Input(int A[], int turn);
  void GameOver(Stage);
  void DataOut();
  int AskAi(int A[], int);
private:
  unsigned int ConvertAtoIndex(int A[]);
  std::vector<std::vector<unsigned int>> stack;
  std::unordered_map<unsigned int,std::array<int,10>> data;
  Stage win_condition;


};


#endif // AI_H
