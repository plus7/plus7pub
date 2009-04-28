#include "environment.h"

Environment::Environment()
{
}

Reward Environment::doAction(Action action)
{
    int newx,newy;
    if(m_cur_status.first > 13 && m_cur_status.first < 17){
        if(m_cur_status.second > 5 && m_cur_status.second < 7){
            //À‚Ì’†
            if(abs(action.first) == 2){
                newx = m_cur_status.first + (action.first/2);
            }
            if(abs(action.second) == 2){
                newy = m_cur_status.second + (action.second/2);
            }

            m_cur_status = Status(newx, newy);
            emit statusChanged(m_cur_status);
            return -1;
        }
    }

    newx = m_cur_status.first + action.first;
    newy = m_cur_status.second + action.second;

    m_cur_status = Status(newx, newy);
    emit statusChanged(m_cur_status);
    return -1;
}

void Environment::initStatus()
{
    m_cur_status.first = 1;
    m_cur_status.second = 1;
}
