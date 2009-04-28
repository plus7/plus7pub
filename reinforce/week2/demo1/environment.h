#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QObject>
#include "defs.h"

class Environment : public QObject
{
    Q_OBJECT
public:
    Environment();
    Reward doAction(Action action);
    void initStatus();
    Status getStatus() { return m_cur_status; }
signals:
    void statusChanged(Status s);
private:
    Status m_cur_status;
};

#endif // ENVIRONMENT_H
