#ifndef MYFIELD_H
#define MYFIELD_H


class myField
{
public:
  myField();
  bool turn(int, bool);
  int rndTurn(bool);
  void reset();
  int state();
private:
  int field[10] {};
};

#endif // MYFIELD_H
