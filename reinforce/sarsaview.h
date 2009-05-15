#ifndef SARSAVIEW_H
#define SARSAVIEW_H

#include <QWidget>
#include <QMap>
#include "defs.h"

class SarsaView : public QWidget
{
    Q_OBJECT
public:
            SarsaView(QWidget * iParent, Qt::WindowFlags iFlags = 0);
            ~SarsaView();

    QSize   sizeHint() const;
    void setQ(QMap< MyQ, Reward > *q){ m_Q = q; }
protected:
    void    paintEvent(QPaintEvent* iPaintEvent);

private:
    void    setup();

    QRect           m_Rectangle;
    QPolygon        m_Polyline;

    QString         m_Text;     // (1)
    QPoint          m_Point;
    QMap< MyQ, Reward > *m_Q;
};

#endif // SARSAVIEW_H
