#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T10:25:04
#
#-------------------------------------------------

QT       += gui core
greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets printsupport
TARGET = ts_v2
CONFIG   -= console
CONFIG   -= app_bundle
CONFIG += c++14
TEMPLATE = app


SOURCES += main.cpp \
    Ui/startwindow.cpp \
    Core/utils.cpp \
    Core/imagedepo.cpp \
    Ui/settingwindow.cpp \
    Ui/maintitlewidget.cpp \
    Ui/plotterwindow.cpp \
    Core/qcustomplot.cpp \
    Core/configurator.cpp \
    Virtual/speedbehavior.cpp \
    Virtual/thermodynamicalbehavior.cpp \
    Virtual/electricalbehavior.cpp \
    Hardware/generator.cpp \
    Core/filesaver.cpp \

HEADERS += \
    Ui/startwindow.h \
    Core/utils.h \
    Core/imagedepo.h \
    Ui/settingwindow.h \
    Ui/maintitlewidget.h \
    Ui/plotterwindow.h \
    Core/qcustomplot.h \
    Core/configurator.h \
    Virtual/iplotbehavior.h \
    Virtual/speedbehavior.h \
    Virtual/thermodynamicalbehavior.h \
    Virtual/electricalbehavior.h \
    Hardware/generator.h \
    Core/filesaver.h \

RESOURCES += \
    res.qrc





