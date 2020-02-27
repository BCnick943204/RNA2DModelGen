#include <QApplication>
#include <QDebug>

#include "graphicswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new GraphicsWindow();

    qInfo() << "Main path: " << a.applicationDirPath();
    return a.exec();
}
