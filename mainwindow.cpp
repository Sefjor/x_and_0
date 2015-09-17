#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure_enum.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setIds();
  connect(&f, &MyField::drawIt, this, &turnMade );
  connect(&f, &MyField::gameFinished, this, resultOut);

  //getting signal with button id for every button in group
  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
      f.Turn(id, Figure::Cross, true);
    });
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow:: turnMade(int where, Figure wichTurn)
{
  if (wichTurn == Figure::Cross) ui->field->button(where)->setText("X");
  else ui->field->button(where)->setText("O");
}

void MainWindow::on_startmatch_clicked()
{
  boardClear();
}

void MainWindow::on_automatch_clicked()
{
  boardClear();
  f.Turn(0, Figure::Cross, false);
  f.Display();
}

void MainWindow::on_automatch_2_clicked(bool rnd)
{
  disconnect(&f, &MyField::gameFinished, 0, 0);
  connect(&f, &MyField::gameFinished, [this](Stage st)
  {
      win_counter.Worker(st);
    });
  int steps = ui->games->displayText().toInt();
  int nextStep = 0;
  int perc = 0;
  for (int i = 0; i < steps; ++i)
    {
      if (i == nextStep)
        {
          ui->mybar->setValue(perc++);
          nextStep += steps / 100;
        }
      f.Reset();
      f.Turn(0, Figure::Cross, false, rnd);
    }
  ui->mybar->setValue(100);
  f.Reset();
  f.Display();
  ui->statusBar->showMessage( QString::fromStdString( win_counter.Results() ) );
  disconnect(&f, &MyField::gameFinished, 0, 0);
  connect(&f, &MyField::gameFinished, this, resultOut);
}

void MainWindow::resultOut(Stage st)
{
  switch (st) {
    case Stage::DRAW:
      ui->statusBar->showMessage("draw");
      break;
    case Stage::WIN_0:
      ui->statusBar->showMessage("0 won");
      break;
    case Stage::WIN_X:
      ui->statusBar->showMessage("X won");
      break;
    default:
      break;
    }
}


void MainWindow::boardClear()
{
  f.Reset();
  for (auto x : ui->field->buttons() )
    x->setText("");
  ui->statusBar->showMessage("");
}
void MainWindow::setIds()
{
  int i = 0;
  for (auto x : ui->field->buttons() )
    ui->field->setId(x, ++i);
}


void MainWindow::on_automatch_3_clicked()
{
on_automatch_2_clicked(true);
}
