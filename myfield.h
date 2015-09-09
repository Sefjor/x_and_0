#ifndef MYFIELD_H
#define MYFIELD_H
#include <QObject>
#include "ai.h"
#include "enum_class_stage.h"
#include "figure_enum.h"
class Ai;


class myField : public QObject
{
Q_OBJECT
public:
  myField(QObject* parent=0);
  void turn(int whereToMove, figure wichTurn, bool Human, bool ai = false);
  int rndTurn();
   int aiTurn();
  void reset();
  Stage state();
  void display();
signals:
  void drawIt(int, figure);
private:
  int field[10] {};
  Ai logX {Stage::WINX};
  Ai log0 {Stage::WIN0};
};

#endif // MYFIELD_H
