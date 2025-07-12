QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++17

SOURCES += \
    cars.cpp \
    mainwindow.cpp

HEADERS += \
    cars.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

!testcase {
    SOURCES += main.cpp
}

testcase {
    QT      += testlib
    SOURCES += test_readfile.cpp
}
