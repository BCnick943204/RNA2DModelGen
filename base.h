#ifndef BASE_H
#define BASE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QSize>
#include <stdio.h>

class Base: public QGraphicsPixmapItem
{
public:
    Base(char);
    int setBasePic(char);
private:
    QSize base_size;
};

#endif // BASE_H
