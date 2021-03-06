#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include "environment.h"

class Agent : public QObject
{
    Q_OBJECT
public:
    Agent(Environment *env, double alpha, double gamma, double eps);
    double alpha() { return m_alpha; }
    double gamma() { return m_gamma; }
    double epsilon() { return m_eps; }
    void setAlpha(double alpha){ m_alpha = alpha; }
    void setGamma(double gamma){ m_gamma = gamma; }
    void setEps(double eps){ m_eps = eps; }
    int doEpisode();
    void initQ();
    void initE();
    bool isFin(Status st);
    void stop();
    Action selectAction(Status s);
public slots:
    void changeAlpha(int i);
    void changeGamma(int i);
    void changeEps(int i);
signals:
    void updateQ();
private:
    Environment *m_env;
    double m_alpha;
    double m_gamma;
    double m_eps;
    bool m_stop;
public:
    QMap< MyQ, Reward > m_Q;
    QMap< MyQ, double > m_e;
};

#endif // AGENT_H
