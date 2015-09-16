#include "myfield.h"
#include <QtGlobal>
myField::myField (QObject* parent)
  : QObject(parent)
{
}

void myField::turn(int whereToMove, figure wichTurn, bool Human, bool ai)
{
  Stage st = state();  // checking victory or draw
  if (st != Stage::NEXT)
    {
      logX.gameOver(st);
      log0.gameOver(st);
      gameFinished(st);
      return;
    }

  if (whereToMove == 0) // 0 means it's comp turn
    whereToMove = aiTurn(wichTurn);

  if (wichTurn == figure::Cross) //logging
    logX.input(field, whereToMove);
  else
    log0.input(field, whereToMove);

  if (field[whereToMove] == 0)  //making turn (writing array)
    field[whereToMove] = wichTurn;
  else return; //can't make this turn

  if (Human)
    drawIt(whereToMove, wichTurn); // turn done signaling to draw

  if ((wichTurn == figure::Cross) || !Human)
    turn(0, wichTurn == figure::Cross ? wichTurn = figure::Zero : wichTurn = figure::Cross, Human, ai); //recursive call of turn with wichTurn inverted;

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

int myField::aiTurn(figure f)
{
  int turn = 0;
  do
    {
      //if turn is impossible tell AI
  turn = (f == figure::Cross) ? logX.askAi(field, turn) : log0.askAi(field, turn);
    }
  while (field[turn] != 0);
  return turn;                     
}


void myField::reset()
{
  for (int i = 1; i<10; ++i)
    field[i] = 0;
}

Stage myField::state()
{
  int solutions [8][3] {{1,2,3},
                        {4,5,6},
                        {7,8,9},
                        {1,4,7},
                        {2,5,8},
                        {3,6,9},
                        {1,5,9},
                        {3,5,7}
                       };
  for (auto f : {figure::Cross, figure::Zero})
    for (int x = 0; x < 8; ++x)
      if (field[solutions[x][0]] == f && field[solutions[x][1]] == f && field[solutions[x][2]] == f)
        return f == figure::Cross ? Stage::WINX : Stage::WIN0;

  bool freePlace;
  for (int i = 1; i < 10; ++i)
    if (field[i] == 0)
      freePlace = true;
  if (!freePlace)
    return Stage::DRAW;

  return Stage::NEXT;
}

void myField::display()
{
  logX.dataOut();
 log0.dataOut();
}



