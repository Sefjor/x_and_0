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
  void turn(int whereToMove, figure isItXorOturn, bool isHumanPlaying, bool RandomVsAi = false);
  int rndTurn();
  int aiTurn(figure);
  void reset();
  Stage state();
  void display();
signals:
  void drawIt(int, figure);
  void gameFinished(Stage);
private:
  int field[10] {};
  Ai logX {Stage::WINX};
  Ai log0 {Stage::WIN0};
};

#endif // MYFIELD_H
