#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "environment.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    env = new Environment();
    agent = new Agent(env, 0.5, 0.5, 0.1); // double alpha, double gamma, double eps
    connect(env, SIGNAL(statusChanged(Status)),
            this, SLOT(recvStatusChanged(Status)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvStatusChanged(Status s)
{

}

void MainWindow::on_initButton_clicked()
{

}

void MainWindow::on_startButton_clicked()
{
    agent->initQ();
    for(int i=0;i<100;i++){
        agent->doEpisode();
    }
}
