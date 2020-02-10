#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <QObject>
#include <QProcess>


class GraphicsWindow: public QObject
{
    Q_OBJECT
public:
    GraphicsWindow();
public slots:
void processDOne(QProcess::ProcessError);
};

#endif // GRAPHICSWINDOW_H
