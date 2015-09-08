#ifndef MYFIELD_H
#define MYFIELD_H
#include <QObject>
#include "ai.h"
class Ai;
enum class Stage {NEXT, WINX, WIN0, DRAW};


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
