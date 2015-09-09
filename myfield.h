#ifndef MYFIELD_H
#define MYFIELD_H
#include <QObject>
#include "ai.h"
#include "enum_class_stage.h"
class Ai;

class myField : public QObject
{
Q_OBJECT
public:
  myField(QObject* parent=0);
  bool turn(int whereToMove, bool xTurn, bool Human);
  int rndTurn();
  void reset();
  Stage state();
signals:
  void drawIt(int, bool);
private:
  int field[10] {};
  Ai logX;
  Ai log0;
};

#endif // MYFIELD_H
