#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setIds();
  connect(&F, &myField::drawIt, this, &turnMade );

  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
      ui->statusBar->showMessage( "clicked: " + QString::number(id) );
      F.turn(id, true, true);
    });

}
MainWindow::~MainWindow()
{
  delete ui;
}




void MainWindow::on_startmatch_clicked()
{
F.reset();
for (auto x : ui->field->buttons() )
  x->setText("");
}



void MainWindow::setIds()
{
  int i = 0;
for (auto x : ui->field->buttons() )
  ui->field->setId(x, ++i);
}

void MainWindow::turnMade(int where, bool cross)
{
 if (cross == true) ui->field->button(where)->setText("X");
 else ui->field->button(where)->setText("O");

}

void MainWindow::on_automatch_clicked()
{
  F.reset();
  for (auto x : ui->field->buttons() )
    x->setText("");
  F.turn(0, true, false);
}
