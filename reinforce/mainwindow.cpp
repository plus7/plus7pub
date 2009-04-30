#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "environment.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    env = new Environment();
    agent = new Agent(env, 0.5, 0.5, 0.1); // double alpha, double gamma, double eps
    ui->alphaCombo->setCurrentIndex(5);
    ui->gammaCombo->setCurrentIndex(5);
    ui->epsilonCombo->setCurrentIndex(4);
    connect(env, SIGNAL(statusChanged(Status)),
            this, SLOT(recvStatusChanged(Status)));
    connect(ui->alphaCombo, SIGNAL(currentIndexChanged(int)),
            agent, SLOT(changeAlpha(int)));
    connect(ui->gammaCombo, SIGNAL(currentIndexChanged(int)),
            agent, SLOT(changeGamma(int)));
    connect(ui->epsilonCombo, SIGNAL(currentIndexChanged(int)),
            agent, SLOT(changeEps(int)));
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

    if(Status(10,10) == Status(10,10)){
        QMessageBox::information(NULL, "", "true");
    }

}

void MainWindow::on_startButton_clicked()
{
    agent->initQ();
    for(int i=0;i<3;i++){
        agent->doEpisode();
    }
}
