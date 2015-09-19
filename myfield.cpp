#include "myfield.h"
#include <QtGlobal>
MyField::MyField (QObject* parent)
  : QObject(parent)
{
}

void MyField::Turn(Settings& settings)
{
  Stage st = State();  // checking victory or draw
  if (st != Stage::NEXT)
    {
      log_x.GameOver(st);
      log_0.GameOver(st);
      emit gameFinished(st);
      Reset();
      return;
    }
  if (settings.turn == 0) // 0 means it's comp turn
    {
    if (settings.is_learning)
    settings.turn = settings.is_cross ? RndTurn() : AiTurn(settings.is_cross);
    else settings.turn = AiTurn(settings.is_cross);
    }

  if (settings.is_cross) //logging
    log_x.Input(field, settings.turn);
  else
    log_0.Input(field, settings.turn);

  if (field[settings.turn] == 0)  //making turn (writing array)
    field[settings.turn] = settings.is_cross + 1;
  else return; //can't make this turn

  if (settings.is_human)
    emit drawIt(settings.turn, settings.is_cross); // turn done, signaling to draw
  if ((settings.is_cross) || !settings.is_human)
    {
      settings.is_cross = !settings.is_cross;
      settings.turn = 0;
       Turn(settings);
    }
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

int MyField::AiTurn(bool f)
{
  int turn = 0;
  do
    {
      //if turn is impossible tell AI
  turn = f ? log_x.AskAi(field, turn) : log_0.AskAi(field, turn);
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
  for (auto f : {Figure::cross, Figure::zero})
    for (int x = 0; x < 8; ++x)
      if (field[solutions[x][0]] == f && field[solutions[x][1]] == f && field[solutions[x][2]] == f)
        return f == Figure::cross ? Stage::WIN_X : Stage::WIN_0;

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



