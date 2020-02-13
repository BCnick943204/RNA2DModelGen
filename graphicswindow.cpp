#include <QGraphicsScene>
#include <QGraphicsView>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>
#include <QTabWidget>
#include <QPalette>
#include <QSvgWidget>
#include <QScrollArea>


#include "graphicswindow.h"
#include "rnagraphicsview.h"
#include "base.h"

GraphicsWindow::GraphicsWindow()
   // : QMainWindow(parent)
    //, ui(new Ui::GraphicsWindow)
{

    QString rnaFoldCmd = "../RNA2DGraphics/ViennaRNA/bin/RNAfold";
    QStringList rnaFoldArgs;
    rnaFoldArgs << "--noPS" << "../RNA2DGraphics/sequences/seq.txt";

    QString rnaPlotCmd = "../RNA2DGraphics/ViennaRNA/bin/RNAplot";
    QStringList rnaPlorArgs;
    rnaPlorArgs << "-o" << "svg";

    qInfo() << "RNAfold arguments: " << rnaFoldArgs;

    QProcess *rnaFold = new QProcess(this);
    QProcess *rnaPlot = new QProcess(this);

    rnaFold->setStandardOutputProcess(rnaPlot);
    //rnaFold->setReadChannel(QProcess::StandardOutput);

    rnaFold->setProgram(rnaFoldCmd);
    rnaFold->setArguments(rnaFoldArgs);
    rnaFold->start(QIODevice::ReadWrite);
    rnaFold->waitForFinished();


   rnaPlot->setProgram(rnaPlotCmd);
   rnaPlot->setArguments(rnaPlorArgs);
   rnaPlot->start();
   rnaPlot->waitForFinished();

   qInfo() << "RNAfold working dir: " << rnaFold->workingDirectory();
   qInfo() << "RNAplot pwd: " << rnaPlot->workingDirectory();
   qInfo() << "RNAplot Errors: " << rnaPlot->readAllStandardError();
   connect(rnaPlot,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(processDOne(QProcess::ProcessError)));

   QTabWidget *tabWindow = new QTabWidget();


   QString fileName = "./rna.svg";
   svgImage = new QSvgWidget(fileName);

   QSvgWidget *svgImageTwo = new QSvgWidget(fileName);
   svgImage->resize(500,500);
   svgImage->setStyleSheet("background-color:white");

   QPalette pal(QPalette::Background, Qt::white);


   QScrollArea *area = new QScrollArea();
   area->setWidget(svgImage);
   area->setAlignment(Qt::AlignCenter);
   area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   area->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
   area->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
   area->setPalette(pal);



   tabWindow->addTab(area, QString("RNA1"));
   tabWindow->addTab(svgImageTwo, QString("RNA2"));
   tabWindow->show();


   //setCentralWidget(svgImage);

}

void GraphicsWindow::processDOne(QProcess::ProcessError error)
{
    qInfo() << error;
}


