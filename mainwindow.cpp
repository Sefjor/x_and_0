#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setIds();

  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
      ui->statusBar->showMessage( "clicked: " + QString::number(id) );
      playerClick(id);
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

void MainWindow::playerClick(int id)
{

if ( F.turn(id, true) )
  {
     ui->field->button(id)->setText("X");
     compTurn();
  }
}




void MainWindow::setIds()
{
  int i = 0;
for (auto x : ui->field->buttons() )
  ui->field->setId(x, ++i);
}

void MainWindow::compTurn()
{
  if (int a = F.rndTurn(false))
  ui->field->button(a)->setText("O");
}
