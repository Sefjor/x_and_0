#ifndef MYFIELD_H
#define MYFIELD_H
#include <QObject>
enum class Stage {NEXT, WINX, WIN0, DRAW};


class myField : public QObject
{
Q_OBJECT
public:
  myField(QObject* parent=0);
  bool turn(int, bool);
  int rndTurn();
  void reset();
  Stage state();
signals:
  void drawIt(int, bool);
private:
  int field[10] {};
};

#endif // MYFIELD_H
