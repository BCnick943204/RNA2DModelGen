#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSvgWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphicsWindow; }
QT_END_NAMESPACE

class GraphicsWindow: public QMainWindow
{
    Q_OBJECT
public:
    GraphicsWindow();
public slots:
void processDOne(QProcess::ProcessError);


private:
    QSvgWidget *svgImage;
    Ui::GraphicsWindow *ui;
};

#endif // GRAPHICSWINDOW_H
