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

  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
      // ui->statusBar->showMessage( "clicked: " + QString::number(id) );
      F.turn(id, figure::Cross, true, true);
    });
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::turnMade(int where, figure wichTurn)
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

void MainWindow::on_automatch_2_clicked()
{
  disconnect(&F, &myField::gameFinished, 0, 0);
  connect(&F, &myField::gameFinished, [=](Stage st)
  {
      winCounter.worker(st);
    });

  for (int i = 0; i<100000; ++i)
    {
      F.reset();
      F.turn(0, figure::Cross, false);
    }
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

