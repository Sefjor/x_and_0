#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myfield.h"
#include "wincounter.h"
class myField;
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void turnMade(int, figure);
  void on_startmatch_clicked();
  void on_automatch_clicked();
  void on_automatch_2_clicked();
  void resultOut(Stage);


private:
  void setIds();
  void boardClear();
  Ui::MainWindow *ui;
  myField F;
  WinCounter winCounter;
};

#endif // MAINWINDOW_H
