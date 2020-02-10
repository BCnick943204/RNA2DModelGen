#include <QGraphicsScene>
#include <QGraphicsView>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>

#include "graphicswindow.h"
#include "rnagraphicsview.h"
#include "base.h"

GraphicsWindow::GraphicsWindow()
{
    // create a scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1000,1000);

    // create a view to visualize items
    RNAGraphicsView* view = new RNAGraphicsView(scene);
  //  view->setStyleSheet("QScrollBar {height:0px;}"); // hide scroll bars
    //view->setStyleSheet("QScrollBar {width:0px;}");
    view->setFixedSize(800,600); // set view to fixed size

/*
    // Add an item to the scene
    Base* a = new Base('A');
    Base* c = new Base('C');
    Base* g = new Base('G');
    Base* u = new Base('U');

*/

    QString exec1 = "../RNA2DGraphics/ViennaRNA/bin/RNAfold";
    QStringList arguments;
    arguments << "../RNA2DGraphics/sequences/seq.txt";// "./sequences/seq.txt";

    qInfo() << arguments;

    QProcess *rnaFold = new QProcess(this);
  //  rnaFold->setWorkingDirectory("../RNA2DGraphics/ViennaRNA/hello");
    rnaFold->setReadChannel(QProcess::StandardOutput);

   // connect(rnaFold,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(processDOne(QProcess::ProcessError)));

    rnaFold->setProgram(exec1);
    rnaFold->setArguments(arguments);
    rnaFold->start(QIODevice::ReadWrite);
    rnaFold->waitForFinished();


   QString plotArgs = rnaFold->readAllStandardOutput();
   int pos = plotArgs.lastIndexOf(" (");
   plotArgs = plotArgs.left(pos);

   QStringList pltArgs;
   pltArgs << plotArgs;
   qInfo() << plotArgs;

   QString exec2 = "../RNA2DGraphics/ViennaRNA/bin/RNAplot";

   QProcess *rnaPlot = new QProcess(this);
 //  rnaFold->setWorkingDirectory("../RNA2DGraphics/ViennaRNA/hello");
   rnaPlot->setReadChannel(QProcess::StandardOutput);

   connect(rnaPlot,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(processDOne(QProcess::ProcessError)));

   rnaPlot->setProgram(exec2);
   rnaPlot->setArguments(pltArgs);
  // rnaPlot->setWorkingDirectory("../RNA2DGraphics/ViennaRNA/");

   rnaPlot->start(QIODevice::ReadWrite);
   rnaPlot->waitForFinished();

///////////////////////////////////////////////////
   QString fileName = "./rna.ps";
           QImage tempImage(fileName);
           if (tempImage.isNull()) {
               qInfo() << "Image is null :'(";
               //QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
               return;
           }
           QImage image = tempImage.convertToFormat(QImage::Format_RGB32);
           QPixmap pixmap = QPixmap::fromImage(image);

           int width = view->geometry().width();
           int height = view->geometry().height();
           //	        QMessageBox::information(this, tr("WIDTH HEIGHT"), tr("Width= %1 Height= %2").arg(QString::number(width, 10), QString::number(height, 10)));
           scene->addPixmap(pixmap.scaled(QSize(
                   (int)scene->width(), (int)scene->height()),
                   Qt::KeepAspectRatio, Qt::SmoothTransformation));
           view->fitInView(QRectF(0, 0, width, height),
                   Qt::KeepAspectRatio);
           view->setScene(scene);
           view->show();

           qInfo() << "here";




}

void GraphicsWindow::processDOne(QProcess::ProcessError error)
{
    qInfo() << error;
}


