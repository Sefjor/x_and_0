#include "myfield.h"
#include <QtGlobal>

myField::myField (QObject* parent)
  : QObject(parent)
{
}

bool myField::turn(int whereToMove, bool xTurn, bool Human)
{
  if (state() != Stage::NEXT)
    return false;
  if (whereToMove == 0)
    whereToMove = rndTurn();
  logX.input(field, whereToMove);
  if (field[whereToMove] == 0)
    field[whereToMove] = 1 + xTurn;
  else return false; //can't make this turn
  drawIt(whereToMove, xTurn);
  if (xTurn || !Human)
    turn(0, !xTurn, Human);
  return true;
}

int myField::rndTurn()
{
  int rnd;
  do {
      rnd = qrand() % 9 + 1;
    }
  while (field[rnd] != 0);
  return rnd;
}

void myField::reset()
{
  for (int i = 1; i<10; ++i)
    field[i] = 0;
}

Stage myField::state()
{
  bool freePlace;
  for (int i = 1; i < 10; ++i)
    if (field[i] == 0)
      freePlace = true;
  if (!freePlace)
    return Stage::DRAW;
  int solutions [8][3] {{1,2,3},
                        {4,5,6},
                        {7,8,9},
                        {1,4,7},
                        {2,5,8},
                        {3,6,9},
                        {1,5,9},
                        {3,5,7}
                       };
  for (auto sign : {1,2})
    for (int x = 0; x < 8; ++x)
      if (field[solutions[x][0]] == sign && field[solutions[x][1]] == sign && field[solutions[x][2]] == sign)
        return sign==1?Stage::WINX:Stage::WIN0 ;
  return Stage::NEXT;
}



