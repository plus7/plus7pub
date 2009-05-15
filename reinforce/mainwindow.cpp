#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "environment.h"

#include <QMessageBox>
#include <QApplication>

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))

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

    ui->sView->setQ(&(agent->m_Q));
    connect(agent, SIGNAL(updateQ()),
            ui->sView, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvStatusChanged(Status s)
{
    QString str;
    str.sprintf("%d %d", s.first, s.second);
    ui->textEdit->append(str);
    QTableWidgetItem *item = ui->tableWidget->item(s.second,s.first);
    if(item){
        QColor c = item->backgroundColor();
        c.setRed(min(c.red() + 1,255));
        item->setBackgroundColor(c);
    }
}

void MainWindow::on_initButton_clicked()
{

    if(Status(10,10) == Status(10,10)){
        QMessageBox::information(NULL, "", "true");
    }
}

void MainWindow::on_startButton_clicked()
{
    stop = false;
    int i,j;
    for(i=0;i<20;i++){
        for(j=0;j<10;j++){
            QTableWidgetItem* item = ui->tableWidget->item(j,i);
            if(item){
                item->setBackground(Qt::SolidPattern);
            }
        }
    }
    env->initStatus();
    agent->initQ();
    agent->initE();
    for(int i=0;i<1000;i++){
        if(stop) break;
        ui->textEdit->append("try");
        int ret = agent->doEpisode();
        QString str;
        str.sprintf("%d",ret);
        ui->textEdit_2->append(str);
    }
}

void MainWindow::on_stopButton_clicked()
{
    stop = true;
    agent->stop();
}
