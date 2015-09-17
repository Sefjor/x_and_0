#include "myfield.h"
#include <QtGlobal>
MyField::MyField (QObject* parent)
  : QObject(parent)
{
}

void MyField::Turn(int whereToMove, Figure wichTurn, bool human, bool rnd)
{
  Stage st = State();  // checking victory or draw
  if (st != Stage::NEXT)
    {
      log_x.GameOver(st);
      log_0.GameOver(st);
      emit gameFinished(st);
      return;
    }

  if (whereToMove == 0) // 0 means it's comp turn
    {
    if (rnd)
    whereToMove = wichTurn == Figure::Cross ? RndTurn() : AiTurn(wichTurn);
    else whereToMove = AiTurn(wichTurn);
    }

  if (wichTurn == Figure::Cross) //logging
    log_x.Input(field, whereToMove);
  else
    log_0.Input(field, whereToMove);

  if (field[whereToMove] == 0)  //making turn (writing array)
    field[whereToMove] = wichTurn;
  else return; //can't make this turn

  if (human)
    emit drawIt(whereToMove, wichTurn); // turn done, signaling to draw

  if ((wichTurn == Figure::Cross) || !human)
    Turn(0, wichTurn == Figure::Cross ? wichTurn = Figure::zero : wichTurn = Figure::Cross, human, rnd); //recursive call of turn with wichTurn inverted;

}

int MyField::RndTurn()
{
  int rnd;
  do {
      rnd = qrand() % 9 + 1;
    }
  while (field[rnd] != 0);
  return rnd;
}

int MyField::AiTurn(Figure f)
{
  int turn = 0;
  do
    {
      //if turn is impossible tell AI
  turn = (f == Figure::Cross) ? log_x.AskAi(field, turn) : log_0.AskAi(field, turn);
    }
  while (field[turn] != 0);
  return turn;
}


void MyField::Reset()
{
  for (int i = 1; i<10; ++i)
    field[i] = 0;
}

inline Stage MyField::State()
{
  static int solutions [8][3] {{1,2,3},
                        {4,5,6},
                        {7,8,9},
                        {1,4,7},
                        {2,5,8},
                        {3,6,9},
                        {1,5,9},
                        {3,5,7}
                       };
  for (auto f : {Figure::Cross, Figure::zero})
    for (int x = 0; x < 8; ++x)
      if (field[solutions[x][0]] == f && field[solutions[x][1]] == f && field[solutions[x][2]] == f)
        return f == Figure::Cross ? Stage::WIN_X : Stage::WIN_0;

  bool freePlace;
  for (int i = 1; i < 10; ++i)
    if (field[i] == 0)
      freePlace = true;
  if (!freePlace)
    return Stage::DRAW;

  return Stage::NEXT;
}

void MyField::Display()
{
  log_x.DataOut();
  log_0.DataOut();
}



