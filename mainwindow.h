#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myfield.h"
#include "wincounter.h"
#include "settings.h"
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
  void turnMade(int, bool);
  void on_startmatch_clicked();
  void on_automatch_clicked();
  void on_automatch_2_clicked(bool randomVsAiMode = false);
  void resultOut(Stage);
  void on_automatch_3_clicked();

private:
  void setIds();
  void boardClear();
  class ProgressBar;
  friend class ProgressBar;
  Ui::MainWindow *ui;
  MyField field;
  WinCounter win_counter;
  Settings settings;
};

#endif // MAINWINDOW_H
