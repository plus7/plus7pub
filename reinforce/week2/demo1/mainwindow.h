#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPair>
#include "environment.h"
#include "agent.h"
#include "defs.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void doEpisode();
public slots:
    void recvStatusChanged(Status s);

private:
    Ui::MainWindow *ui;
    Environment *env;
    Agent *agent;

private slots:
    void on_startButton_clicked();
    void on_initButton_clicked();
};

#endif // MAINWINDOW_H
