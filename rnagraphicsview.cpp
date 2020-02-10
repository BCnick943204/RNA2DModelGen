#include "rnagraphicsview.h"


RNAGraphicsView::RNAGraphicsView(QGraphicsScene *scene): QGraphicsView(scene)
{

}

void RNAGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(_isPanning){
        int horBarVal = horizontalScrollBar()->value();
        int verBarVal = verticalScrollBar()->value();

        horizontalScrollBar()->setValue(horBarVal - (event->x() - _panInitX));
        verticalScrollBar()->setValue(verBarVal - (event->y() - _panInitY));

        _panInitX = event->x();
        _panInitY = event->y();
        return;
    }
    event->ignore();
}

void RNAGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        _isPanning = true;
        _panInitX = event->x();
        _panInitY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void RNAGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        _isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}


