#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>

#include <QPalette>
#include <QSvgWidget>
#include <QScrollArea>


#include "graphicswindow.h"
#include "rnamodelgen.h"
#include "rnagraphicsview.h"
#include "base.h"

GraphicsWindow::GraphicsWindow()
{


    RNAModelGen *rnaGen = new RNAModelGen();
    rnaGen->generate2DModel("AGAGAGAGUUUUUUUUGUGUGUGUGUG");



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



}

void GraphicsWindow::processDOne(QProcess::ProcessError error)
{
    qInfo() << error;
}


