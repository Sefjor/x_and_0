#ifndef AI_H
#define AI_H
#include <vector>
#include <QDebug>

class Ai
{
public:
  Ai();
  void input(int A[10], int turn);
private:

  std::vector<std::vector<unsigned int>> stack;
std::vector<std::vector<unsigned int>> Data;
};


#endif // AI_H
