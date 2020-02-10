#ifndef RNAGRAPHICSVIEW_H
#define RNAGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QScrollBar>

class RNAGraphicsView: public QGraphicsView
{
public:
    RNAGraphicsView(QGraphicsScene*);
private:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    bool _isPanning;
    int _panInitX, _panInitY;
};

#endif // RNAGRAPHICSVIEW_H
