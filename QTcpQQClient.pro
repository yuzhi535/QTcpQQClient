QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpclient.cpp \
    screenwidget.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    mytcpclient.h \
    screenwidget.h

FORMS += \
    dialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    QTcpQQClient_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    ico.qrc \
    png.qrc \
    sound.qrc
