#include "ai.h"
enum bonuses
{
  loose = -1000,
  win = 1,
  draw = 0
};

Ai::Ai(Stage st)
{
  win_condition = st;
}

void Ai::Input(int A[], int turn)
{
  //stack format: vector of {1:custom index, 2:where to make a turn}
  stack.push_back({ConvertAtoIndex(A), static_cast<unsigned int>(turn)});//fail safe here as turn is always 0..9;
}

void Ai::GameOver(Stage st)
{
  int bonus{};
  if (st == Stage::DRAW)
      bonus = bonuses::draw;
  else
      bonus = st == win_condition ? bonuses::win : bonuses::loose;

  for (auto x : stack)
    data[ x[0] ] [ x[1] ] += bonus;
  stack.clear();
}

void Ai::DataOut()
{
  for (auto x : data)
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

int Ai::AskAi(int A[], int impossibleTurn)
{
  unsigned int index = ConvertAtoIndex(A);
  if (impossibleTurn != 0)
    data[index][impossibleTurn] = std::numeric_limits<int>::lowest();

  int max = std::numeric_limits<int>::lowest();
  int maxI = 1;
  for (int i = 1; i<10; ++i)
    if (max < data[index][i])
      {
        max = data[index][i];
        maxI = i;
      }
  return maxI;
}


unsigned int Ai::ConvertAtoIndex(int A[])
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

