#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure_enum.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setIds();
  connect(&F, &myField::drawIt, this, &turnMade );
  connect(&F, &myField::gameFinished, this, resultOut);

  //getting signal with button id for every button in group
  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
      F.turn(id, figure::Cross, true);
    });
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow:: turnMade(int where, figure wichTurn)
{
  if (wichTurn == figure::Cross) ui->field->button(where)->setText("X");
  else ui->field->button(where)->setText("O");
}

void MainWindow::on_startmatch_clicked()
{
  boardClear();
}

void MainWindow::on_automatch_clicked()
{
  boardClear();
  F.turn(0, figure::Cross, false);
  F.display();
}

void MainWindow::on_automatch_2_clicked(bool rnd)
{
  disconnect(&F, &myField::gameFinished, 0, 0);
  connect(&F, &myField::gameFinished, [this](Stage st)
  {
      winCounter.worker(st);
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
      F.reset();
      F.turn(0, figure::Cross, false, rnd);
    }
  ui->mybar->setValue(100);
  F.reset();
  F.display();
  ui->statusBar->showMessage( QString::fromStdString( winCounter.results() ) );
  disconnect(&F, &myField::gameFinished, 0, 0);
  connect(&F, &myField::gameFinished, this, resultOut);
}

void MainWindow::resultOut(Stage st)
{
  switch (st) {
    case Stage::DRAW:
      ui->statusBar->showMessage("draw");
      break;
    case Stage::WIN0:
      ui->statusBar->showMessage("0 won");
      break;
    case Stage::WINX:
      ui->statusBar->showMessage("X won");
      break;
    default:
      break;
    }
}


void MainWindow::boardClear()
{
  F.reset();
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
