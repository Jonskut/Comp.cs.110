QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameboard.cpp \
    gameboardwidget.cpp \
    gameoverdialog.cpp \
    invalidstartdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    pausedialog.cpp \
    utils.cpp

HEADERS += \
    gameboard.hh \
    gameboardwidget.hh \
    gameoverdialog.hh \
    invalidstartdialog.hh \
    mainwindow.hh \
    pausedialog.hh \
    utils.hh

FORMS += \
    gameboardwidget.ui \
    gameoverdialog.ui \
    invalidstartdialog.ui \
    mainwindow.ui \
    pausedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    mainwindow.qrc

DISTFILES += \
    Resources/circle-black.png \
    Resources/circle-white.png
