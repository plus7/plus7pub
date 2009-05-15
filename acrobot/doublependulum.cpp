#include "doublependulum.h"
#include <math.h>
#define M_1 1
#define M_2 1
#define L_1 1
#define L_2 1
#define LC_1 0.5
#define LC_2 0.5
#define I_1 1
#define I_2 1
#define Gravity 9.8



DoublePendulum::DoublePendulum(double deg1, double deg2)
        : m_degree1(deg1), m_degree2(deg2)
{

}

void DoublePendulum::init(double deg1, double deg2)
{
    m_degree1 = deg1;
    m_degree2 = deg2;
}

double DoublePendulum::acc1()
{
    return - (d2() * acc2() + phi()) / d1();
}
double DoublePendulum::acc2()
{
    return (d2()/d1()*phi1() - M_2*L_1*L_2*pow(m_speed1,2)*sin(m_degree2) - phi2())/(M_2*pow(LC_2,2) + I_2 - pow(d2(),2)/d1())
}
double DoublePendulum::d1()
{
    return M_1*pow(LC_1,2) + M_2*(pow(L_1,2) + pow(LC_2,2) + 2*L_1*L_2*cos(m_degree2)) + I_1 + I_2;
}
double DoublePendulum::d2()
{
    return M_2*(pow(LC_2,2) + L_1*L_2*cos(m_degree2)) + I_2;
}
double DoublePendulum::phi1()
{
    return - M_2*L_1*LC_2*pow(acc2(),2)*sin(m_degree2) - 2*M_2*L_1*LC_2*acc1()*acc2()*sin(M_degree2)
           + (()*Gravity*cos(m_degree1 - )) + m_degree2;
}
double DoublePendulum::phi2()
{
    return M_2*LC_2*Gravity*cos(m_degree1 + m_degree2 - (M_PI/2.0));
}
