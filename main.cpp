#include <QApplication>
#include <QDebug>

#include "graphicswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new GraphicsWindow();

    return a.exec();
}
