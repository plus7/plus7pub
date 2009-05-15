#ifndef DOUBLEPENDULUM_H
#define DOUBLEPENDULUM_H

#include <QObject>

class DoublePendulum : public QObject
{
    Q_OBJECT
public:
    DoublePendulum(double deg1, double deg2);
    void init(double deg1, double deg2);
    void doStep();
    void getAcc1();
    void getAcc2();
    void getD1();
    void getD2();
    void getPhi1();
    void getPhi2();
private:
    double m_degree1, m_degree2;
    double m_speed1, m_speed2;
};

#endif // DOUBLEPENDULUM_H
