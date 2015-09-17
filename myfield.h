#ifndef MYFIELD_H
#define MYFIELD_H
#include <QObject>
#include "ai.h"
#include "enum_class_stage.h"
#include "figure_enum.h"
class Ai;


class MyField : public QObject
{
Q_OBJECT
public:
  MyField(QObject* parent=0);
  void Turn(int whereToMove, Figure isItXorOturn, bool isHumanPlaying, bool RandomVsAi = false);
  int RndTurn();
  int AiTurn(Figure);
  void Reset();
  Stage State();
  void Display();
signals:
  void drawIt(int, Figure);
  void gameFinished(Stage);
private:
  int field[10] {};
  Ai log_x {Stage::WIN_X};
  Ai log_0 {Stage::WIN_0};
};

#endif // MYFIELD_H
