#include "ai.h"

Ai::Ai(Stage st)
{
  winCondition = st;
}

void Ai::input(int A[], int turn)
{
  unsigned int x = 1;
  unsigned int result = 0;
  for(int i = 0; i<10; ++i)
    {
      result += A[i] * x;
      x *= 10;
    }
  stack.push_back({result, static_cast<unsigned int>(turn)});//fail safe here as turn is 1 or 0;
  //qDebug() << result;
}

void Ai::gameOver(Stage st)
{
  if (winCondition == Stage::WINX)
qDebug() << "i am cross";
  else
    qDebug() << "i am zero";

  if (st == Stage::DRAW)
    qDebug() << "and it's draw";
  else
    {
      if (st == winCondition)
        qDebug() << "and I won";
      else
        qDebug() << "and I lost";
    }
  qDebug() << "--------";
}

