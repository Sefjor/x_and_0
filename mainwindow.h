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
  void setIds();
  void compTurn();
  void playerClick(int);

private slots:

  void on_startmatch_clicked();

private:
  Ui::MainWindow *ui;
   myField F;
};

#endif // MAINWINDOW_H
