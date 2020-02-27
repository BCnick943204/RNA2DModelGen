QT       += core gui svg widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    base.cpp \
    graphicswindow.cpp \
    main.cpp \
    rnagraphicsview.cpp \
    rnamodelgen.cpp

HEADERS += \
    base.h \
    graphicswindow.h \
    rnagraphicsview.h \
    rnamodelgen.h

RESOURCES += \
    res.qrc

