#include "sarsaview.h"
#include <QPainter>
#include <QPen>
SarsaView::SarsaView(QWidget * iParent, Qt::WindowFlags iFlags)
 : QWidget(iParent, iFlags), m_Q(NULL)
{
    setup();

    setBackgroundRole(QPalette::Base);  // (2)
    setAutoFillBackground(true);
}

SarsaView::~SarsaView()
{

}

QSize
SarsaView::sizeHint() const
{
    return QSize(350, 250);
}

void
SarsaView::paintEvent(QPaintEvent* iPaintEvent)
{
    QPainter painter(this);
    if(!m_Q) return;

    // レンダーヒント
    painter.setRenderHint(QPainter::Antialiasing);

    // ペン
    QPen pen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);   // (4)
    painter.setPen(pen);

    // ブラシ
    QBrush brush(Qt::magenta, Qt::CrossPattern);       // (5)
    painter.setBrush(brush);

    // フォント
    QFont font;                     // (6)
    font.setPointSize(30);
    painter.setFont(font);

    // 描画
    //painter.drawRect(m_Rectangle);
    //painter.drawPolyline(m_Polyline);
    //painter.drawText(m_Point, m_Text);
    int i,j;
    Action a;
    Status s;
    int grid;
    Reward d;
    QMap<MyQ, Reward>::iterator p;
    grid = 30;
    for(i=0;i<19;i++){
        for(j=0;j<9;j++){
            s = Status(i,j);
            p = m_Q->find(MyQ(s,Action(1,0)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid+d*4,j*grid));
            }
            p = m_Q->find(MyQ(s,Action(0,1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid,j*grid+d*4));
            }
            p = m_Q->find(MyQ(s,Action(-1,0)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid-d*4,j*grid));
            }
            p = m_Q->find(MyQ(s,Action(0,-1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid,j*grid-d*4));
            }
            p = m_Q->find(MyQ(s,Action(1,1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid+d*4,j*grid+d*4));
            }
            p = m_Q->find(MyQ(s,Action(1,-1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid+d*4,j*grid-d*4));
            }
            p = m_Q->find(MyQ(s,Action(-1,1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid-d*4,j*grid+d*4));
            }
            p = m_Q->find(MyQ(s,Action(-1,-1)));
            if(p != m_Q->end()){
                d = p.value();
                painter.drawLine(QPointF(i*grid,j*grid),QPointF(i*grid-d*4,j*grid-d*4));
            }
        }
    }

}

void
SarsaView::setup()
{
    // 四角形
    m_Rectangle = QRect(20, 20, 130, 100);

    // 折れ線(Polyline)
    m_Polyline.push_back(QPoint(180, 120));
    m_Polyline.push_back(QPoint(190, 30));
    m_Polyline.push_back(QPoint(300, 130));
    m_Polyline.push_back(QPoint(320, 30));

    // テキスト
    m_Text = QString::fromLocal8Bit("Qtプログラミング");   // (3)
    m_Point.setX(30);
    m_Point.setY(200);
}
