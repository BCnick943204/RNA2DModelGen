#include "rnamodelgen.h"

#include <QTemporaryFile>
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

    // start RNAfold
    rnaFold->setProgram(rnaFoldCmd);
    rnaFold->setArguments(rnaFoldArgs);
    rnaFold->setStandardOutputProcess(rnaPlot);     // pipe stdout of rnaFold to rnaPlot
    rnaFold->start(QIODevice::ReadWrite);
    rnaFold->waitForFinished();


    // start RNAplot
    rnaPlot->setProgram(rnaPlotCmd);
    rnaPlot->setArguments(rnaPlotArgs);
    rnaPlot->start();

    rnaPlot->waitForFinished();


}

void RNAModelGen::processError(QProcess::ProcessError error){
    qInfo() << error;
}


