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
  //getting signal with button id for every button in group

  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
      ui->statusBar->showMessage( "clicked: " + QString::number(id) );
      F.turn(id, figure::Cross, true);
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
  F.reset();
  for (auto x : ui->field->buttons() )
    x->setText("");
}

void MainWindow::on_automatch_clicked()
{
  F.reset();
  for (auto x : ui->field->buttons() )
    x->setText("");
  F.turn(0, figure::Cross, false);
  F.display();
}
void MainWindow::setIds()
{
  int i = 0;
  for (auto x : ui->field->buttons() )
    ui->field->setId(x, ++i);

}


void MainWindow::on_automatch_2_clicked()
{
  for (int i = 0; i<10000; ++i)
    {
      F.reset();
      F.turn(0, figure::Cross, false);
    }
  F.display();
}

void MainWindow::on_startmatch_ai_clicked()
{
  F.reset();
  for (auto x : ui->field->buttons() )
    x->setText("");
  F.turn(0, figure::Cross, false);
}
