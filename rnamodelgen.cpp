#include "rnamodelgen.h"

#include <QTemporaryFile>
#include <QSaveFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

RNAModelGen::RNAModelGen()
{
    // configure the processes (RNAfold and RNAplot)
    rnaFoldCmd = "../RNA2DGraphics/ViennaRNA/bin/RNAfold";
    rnaPlotCmd = "../RNA2DGraphics/ViennaRNA/bin/RNAplot";

    QDir dir;
    qInfo() << dir.absolutePath();


}

void RNAModelGen::generate2DModel(QString rnaSequence){

    //initialize the QProcesses
    rnaFold = new QProcess(this);
    rnaPlot = new QProcess(this);


    // generate temp file for RNAFold input
    QTemporaryFile *seq = new QTemporaryFile();
    seq->setAutoRemove(false);

    if(!seq->open()){
        qInfo() << "error opening temp file";
    }

    // write to temporary file
    QTextStream out(seq);
    out << rnaSequence;
    out.flush(); // write sequence immediately to file
    seq->waitForReadyRead(-1);

    if(!seq->isReadable())
        qInfo() << "Not ready to read file";

    // set process argumemts
    rnaFoldArgs << "--noPS" << seq->fileName();
    rnaPlotArgs << "-o" << "svg";

    qInfo() << rnaFoldArgs;

   // start RNAfold;
    rnaFold->setProgram(rnaFoldCmd);
    rnaFold->setArguments(rnaFoldArgs);
    rnaFold->setStandardOutputProcess(rnaPlot);
    rnaFold->start(QIODevice::ReadWrite);
    rnaFold->waitForFinished();

    // generate unique file to save .svg as

    QFile *rnaDotBracket = new QFile("/tmp/RNA2DGraphics.FRVAlH");
    rnaDotBracket->open(QIODevice::ReadWrite);
    if(!rnaDotBracket->isOpen()){
        qInfo() << "NOT OPEN";
        qInfo() << rnaDotBracket->errorString();
    }
    QByteArray *rawFile = new QByteArray(rnaDotBracket->readAll());


    // start RNAplot
    rnaPlot->setProgram(rnaPlotCmd);
    rnaPlot->setArguments(rnaPlotArgs);
    rnaPlot->setStandardOutputFile("myTest.svg");
    rnaPlot->start(QIODevice::ReadWrite);
    rnaPlot->write(*rawFile);
    rnaPlot->waitForFinished();


}

void RNAModelGen::processError(QProcess::ProcessError error){
    qInfo() << error;
}


