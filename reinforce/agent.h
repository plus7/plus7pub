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
    void doEpisode();
    void initQ();
    bool isFin(Status st);
    Action selectAction(Status s);
public slots:
    void changeAlpha(int i);
    void changeGamma(int i);
    void changeEps(int i);
private:
    Environment *m_env;
    double m_alpha;
    double m_gamma;
    double m_eps;
    QMap< MyQ, Reward > m_Q;
};

#endif // AGENT_H
