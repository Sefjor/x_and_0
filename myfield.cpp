#include "myfield.h"
#include <QtGlobal>

myField::myField()
{
}

bool myField::turn(int num, bool x)
{
  if (state() != 0)
    return false;
  if (field[num] == 0)
    field[num] = 1 + x;
  else return false; //can't make this turn
  return true;
}

int myField::rndTurn(bool x)
{
  if (state() != 0)
    return 0;
int rnd;
    do {
      rnd = qrand() % 9 + 1;
    }
          while (field[rnd] != 0);
   field[rnd] = x + 1;
   return rnd;
}

void myField::reset()
{
  for (int i = 1; i<10; ++i)
    field[i] = 0;
}

int myField::state()
{ // 0 = turn possible, 1 = 0 won, 2 = X won, 3 = draw
  bool freePlace;
  for (int i = 1; i < 10; ++i)
    if (field[i] == 0)
      freePlace = true;
  if (!freePlace)
    return 3;
  int solutions [8][3] { {1,2,3},
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
  return sign;
  return 0;
}



