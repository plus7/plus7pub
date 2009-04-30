#include "agent.h"

Agent::Agent(Environment *env, double alpha, double gamma, double eps)
        :m_env(env), m_alpha(alpha), m_gamma(gamma), m_eps(eps)
{
}

void Agent::initQ()
{
    m_Q.clear();
    int i,j;
    for(i=0;i<20;i++){
        for(j=0;j<10;j++){
            m_Q.insert(MyQ(Status(i,j), Action(1,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,0)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(0,-1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(1,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(1,-1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,1)), 0);
            m_Q.insert(MyQ(Status(i,j), Action(-1,-1)), 0);

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
        case 1:
        setEps(0.0001);
        case 2:
        setEps(0.001);
        case 3:
        setEps(0.01);
        case 4:
        setEps(0.1);
        case 5:
        setEps(1.0);
        default:
        setEps(0);
    }
}

Action Agent::selectAction(Status s)
{
    Reward max = -100000000;
    Action a;
    QMap<MyQ, Reward>::iterator p;
    p = m_Q.find(MyQ(s,Action(1,0)));
    if(p != m_Q.end()){
        max = p.value();
    }
    p = m_Q.find(MyQ(s,Action(-1,0)));
    if(p != m_Q.end()){
        if (p.value() > max) {max = p.value(); a.first = 1; a.second = 0;}
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

    return a;
}

void Agent::doEpisode()
{
    m_env->initStatus();

    Status s = m_env->getStatus();
    Action a = selectAction(s);
    while(!isFin(m_env->getStatus())){
        Reward r = m_env->doAction(a);
        Status s_dash = m_env->getStatus();

        Action a_dash = selectAction(s_dash);

        Reward old_Q_sa = m_Q.find(MyQ(s, a)).value();
        Reward old_Q_sa_dash = m_Q.find(MyQ(s_dash, a_dash)).value();

        m_Q[MyQ(s, a)] = old_Q_sa + m_alpha*(r + m_gamma*old_Q_sa_dash - old_Q_sa);
        s = s_dash;
        a = a_dash;
    }
}

bool Agent::isFin(Status st)
{
    if(st == Status(19, 9)) return true;
    if(st.first < 0 || st.first >= 20) return true;
    if(st.second < 0 || st.second >= 10) return true;
    return false;
}
