#include "ai.h"
enum bonuses
{
  loose = -1000,
  win = 1,
  draw = 0
};

Ai::Ai(Stage st)
{
  winCondition = st;
}

void Ai::input(int A[], int turn)
{
  //stack format: vector of {1:custom index, 2:where to make a turn}
  stack.push_back({convertAtoIndex(A), static_cast<unsigned int>(turn)});//fail safe here as turn is 1 or 0;
}

void Ai::gameOver(Stage st)
{
  int bonus{};
  if (st == Stage::DRAW)
      bonus = bonuses::draw;
  else
      bonus = st == winCondition ? bonuses::win : bonuses::loose;

  for (auto x : stack)
    Data[ x[0] ] [ x[1] ] += bonus;
  stack.clear();
}

void Ai::dataOut()
{
  for (auto x : Data)
    {
      QDebug debug = qDebug();
      if (x.first == 0 || x.first == 20000)
        {
          debug << x.first << ": " ;
          for (int i = 1; i<10; ++i)
            debug << x.second[i];
        }

    }
}

int Ai::askAi(int A[], int impossibleTurn)
{
  unsigned int index = convertAtoIndex(A);
  if (impossibleTurn != 0)
    Data[index][impossibleTurn] = std::numeric_limits<int>::lowest();

  int max = std::numeric_limits<int>::lowest();
  int maxI = 1;
  for (int i = 1; i<10; ++i)
    if (max < Data[index][i])
      {
        max = Data[index][i];
        maxI = i;
      }
  return maxI;
}


unsigned int Ai::convertAtoIndex(int A[])
{
  unsigned int x = 1;
  unsigned int result = 0;
  for(int i = 9; i>0; --i)
    {
      result += A[i] * x;
      x *= 10;
    }
  return result;
}

