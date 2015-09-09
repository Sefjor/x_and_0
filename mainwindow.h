#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myfield.h"
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

  void on_startmatch_ai_clicked();

private:
   void setIds();
  Ui::MainWindow *ui;
   myField F;
};

#endif // MAINWINDOW_H
