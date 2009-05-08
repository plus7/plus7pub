#include "agent.h"
#include <stdlib.h>
#include <time.h>
#include <QApplication>
Agent::Agent(Environment *env, double alpha, double gamma, double eps)
        :m_env(env), m_alpha(alpha), m_gamma(gamma), m_eps(eps)
{
    srand( (unsigned) time(NULL) );
}

void Agent::initQ()
{   //m_Q.insert(MyQ(Status(i,j), Action(0,0)), 0);
    m_Q.clear();
    int i,j;

    m_Q.insert(MyQ(Status(0,0), Action(1,0)), 0);
    m_Q.insert(MyQ(Status(0,0), Action(1,1)), 0);
    m_Q.insert(MyQ(Status(0,0), Action(0,1)), 0);

    m_Q.insert(MyQ(Status(19,0), Action(0,1)), 0);
    m_Q.insert(MyQ(Status(19,0), Action(-1,1)), 0);
    m_Q.insert(MyQ(Status(19,0), Action(-1,0)), 0);

    m_Q.insert(MyQ(Status(0,9), Action(1,0)), 0);
    m_Q.insert(MyQ(Status(0,9), Action(1,-1)), 0);
    m_Q.insert(MyQ(Status(0,9), Action(0,-1)), 0);

    m_Q.insert(MyQ(Status(19,9), Action(-1,0)), 0);
    m_Q.insert(MyQ(Status(19,9), Action(-1,-1)), 0);
    m_Q.insert(MyQ(Status(19,9), Action(0,-1)), 0);

    for(i=1;i<19;i++){
        m_Q.insert(MyQ(Status(i,0), Action(1,0)), 0);
        m_Q.insert(MyQ(Status(i,0), Action(-1,0)), 0);
        m_Q.insert(MyQ(Status(i,0), Action(1,1)), 0);
        m_Q.insert(MyQ(Status(i,0), Action(-1,1)), 0);
        m_Q.insert(MyQ(Status(i,0), Action(0,1)), 0);

        m_Q.insert(MyQ(Status(i,9), Action(1,0)), 0);
        m_Q.insert(MyQ(Status(i,9), Action(-1,0)), 0);
        m_Q.insert(MyQ(Status(i,9), Action(1,-1)), 0);
        m_Q.insert(MyQ(Status(i,9), Action(-1,-1)), 0);
        m_Q.insert(MyQ(Status(i,9), Action(0,-1)), 0);
    }
    for(j=1;j<9;j++){
        m_Q.insert(MyQ(Status(0, i), Action(0,1)), 0);
        m_Q.insert(MyQ(Status(0, i), Action(0,-1)), 0);
        m_Q.insert(MyQ(Status(0, i), Action(1,1)), 0);
        m_Q.insert(MyQ(Status(0, i), Action(1,-1)), 0);
        m_Q.insert(MyQ(Status(0, i), Action(1,0)), 0);

        m_Q.insert(MyQ(Status(19,i), Action(0,1)), 0);
        m_Q.insert(MyQ(Status(19,i), Action(0,-1)), 0);
        m_Q.insert(MyQ(Status(19,i), Action(-1,1)), 0);
        m_Q.insert(MyQ(Status(19,i), Action(-1,-1)), 0);
        m_Q.insert(MyQ(Status(19,i), Action(-1,0)), 0);
    }
    for(i=0;i<20;i++){
        for(j=0;j<10;j++){
            m_Q.insert(MyQ(Status(i,j), Action(0,0)), 0);
        }
    }
    for(i=1;i<19;i++){
        for(j=1;j<9;j++){
            m_Q.insert(MyQ(Status(i,j), Action(1,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,-1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(1,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(1,-1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,-1)), 0);
        }
    }
    for(i=2;i<18;i++){
        for(j=2;j<8;j++){
            m_Q.insert(MyQ(Status(i,j), Action(2,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-2,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,2)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,-2)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(2,2)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-2,2)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(2,-2)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-2,-2)), 0);
        }
    }
}

void Agent::changeAlpha(int i)
{
    setAlpha(i/10);
}

void Agent::changeGamma(int i)
{
    setGamma(i/10);
}

void Agent::changeEps(int i)
{
    switch(i){
        case 0:
        setEps(0);
        break;
        case 1:
        setEps(0.0001);
        break;
        case 2:
        setEps(0.001);
        break;
        case 3:
        setEps(0.01);
        break;
        case 4:
        setEps(0.1);
        break;
        case 5:
        setEps(0.3);
        break;
        case 6:
        setEps(1.0);
        break;
        default:
        setEps(0);
    }
}

Action Agent::selectAction(Status s)
{
    Reward max = -100000000;
    Action a;
    QMap<MyQ, Reward>::iterator p;

    int ra = rand();
    double eps = (double)ra / (double)RAND_MAX;

    if(eps < m_eps){
        switch(ra%8){
            case 0:
            a.first = 1;
            a.second = 0;
            break;
            case 1:
            a.first = -1;
            a.second = 0;
            break;
            case 2:
            a.first = 0;
            a.second = -1;
            break;
            case 3:
            a.first = 0;
            a.second = 1;
            break;
            case 4:
            a.first = 1;
            a.second = 1;
            break;
            case 5:
            a.first = 1;
            a.second = -1;
            break;
            case 6:
            a.first = -1;
            a.second = 1;
            break;
            default:
            a.first = -1;
            a.second = -1;
        }
        if(a.first==-1 && s.first==0){a.first = 1;}
        if(a.second==-1 && s.second==0){a.second = 1;}
        if(a.first==1 && s.first==19){a.first = -1;}
        if(a.second==1 && s.second==9){a.second = -1;}
    }
    else{
    p = m_Q.find(MyQ(s,Action(1,0)));
    if(p != m_Q.end()){
        max = p.value();
        a.first = 1;
        a.second = 0;
    }
    p = m_Q.find(MyQ(s,Action(-1,0)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = -1; a.second = 0;}
    }
    p = m_Q.find(MyQ(s,Action(0,-1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = 0; a.second = -1;}
    }
    p = m_Q.find(MyQ(s,Action(0,1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = 0; a.second = 1;}
    }
    p = m_Q.find(MyQ(s,Action(1,1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = 1; a.second = 1;}
    }
    p = m_Q.find(MyQ(s,Action(-1,1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = -1; a.second = 1;}
    }
    p = m_Q.find(MyQ(s,Action(1,-1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = 1; a.second = -1;}
    }
    p = m_Q.find(MyQ(s,Action(-1,-1)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = -1; a.second = -1;}
    }
//    p = m_Q.find(MyQ(s,Action(2,0)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(2,0);}
//    }
//    p = m_Q.find(MyQ(s,Action(-2,0)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(-2,0);}
//    }
//    p = m_Q.find(MyQ(s,Action(0,-2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(0,-2);}
//    }
//    p = m_Q.find(MyQ(s,Action(0,2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(0,2);}
//    }
//    p = m_Q.find(MyQ(s,Action(2,2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(2,2);}
//    }
//    p = m_Q.find(MyQ(s,Action(-2,2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(-2,2);}
//    }
//    p = m_Q.find(MyQ(s,Action(2,-2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(2,-2);}
//    }
//    p = m_Q.find(MyQ(s,Action(-2,-2)));
//    if(p != m_Q.end()){
//        if (p.value() > max) {max = p.value(); a = Action(-2,-2);}
//    }
    }

    return a;
}

int Agent::doEpisode()
{
    m_stop = false;
    m_env->initStatus();
    int ret = 0;
    Status s = m_env->getStatus();
    Action a = selectAction(s);
    while(!isFin(m_env->getStatus()) && !m_stop){
        QApplication::processEvents();
        Reward r = m_env->doAction(a);
        Status s_dash = m_env->getStatus();

        Action a_dash = selectAction(s_dash);

        Reward old_Q_sa = m_Q.find(MyQ(s, a)).value();
        Reward old_Q_sa_dash = m_Q.find(MyQ(s_dash, a_dash)).value();

        m_Q[MyQ(s, a)] = old_Q_sa + m_alpha*(r + m_gamma*old_Q_sa_dash - old_Q_sa);
        s = s_dash;
        a = a_dash;
        ret++;
    }
    return ret;
}

bool Agent::isFin(Status st)
{
    if(st == Status(18, 7)) return true;
    if(st.first < 0 || st.first >= 20) return true;
    if(st.second < 0 || st.second >= 10) return true;
    return false;
}

void Agent::stop()
{
    m_stop = true;
}
