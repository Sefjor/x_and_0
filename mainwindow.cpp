#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure_enum.h"
class MainWindow::ProgressBar {
public:
  ProgressBar(int max, MainWindow *q) : parent(q), max_steps{max}, next_step{0}, percent{0} {}
  ~ProgressBar() {parent->ui->mybar->setValue(100);}
 inline void operator()(int step)
  {
    if (step == next_step)
      {
parent->ui->mybar->setValue(percent++);
        next_step += max_steps / 100;
      }
  }
private:
   MainWindow* parent;
   int max_steps;
  int next_step;
  int percent;

};

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setIds();
  connect(&field, &MyField::drawIt, this, &turnMade );
  connect(&field, &MyField::gameFinished, this, resultOut);

  //getting signal with button id for every button in group
  connect(ui->field, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
      field.Turn(id, Figure::cross, true);
    });
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow:: turnMade(int where, Figure wichTurn)
{
  if (wichTurn == Figure::cross) ui->field->button(where)->setText("X");
  else ui->field->button(where)->setText("O");
}

void MainWindow::on_startmatch_clicked()
{
  boardClear();
}

void MainWindow::on_automatch_clicked()
{
  boardClear();
  field.Turn(0, Figure::cross, false);
  field.Display();
}

void MainWindow::on_automatch_2_clicked(bool rnd)
{
  disconnect(&field, &MyField::gameFinished, 0, 0);
  connect(&field, &MyField::gameFinished, [this](Stage st)
  {
      win_counter.Worker(st);
    });

  int steps = ui->games->displayText().toInt();
  ProgressBar bar(steps, this);
  for (int i = 0; i < steps; ++i)
    {
      bar(i);
      field.Reset();
      field.Turn(0, Figure::cross, false, rnd);
    }
  field.Reset();
  field.Display();
  ui->statusBar->showMessage( QString::fromStdString( win_counter.Results() ) );
  disconnect(&field, &MyField::gameFinished, 0, 0);
  connect(&field, &MyField::gameFinished, this, resultOut);
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
  field.Reset();
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

