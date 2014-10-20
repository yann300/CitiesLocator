TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mainwindow.cpp \
    city.cpp \
    timer.cpp \
    citiesresolver.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    city.h \
    timer.h \
    citiesresolver.h

OTHER_FILES +=

QT += xml

QT += webkitwidgets

