QT       += core gui
QT += network
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop-Debug/release/ -lDLLRestAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop-Debug/debug/ -lDLLRestAPI
else:unix:!macx: LIBS += -L$$PWD/../build-DLLRestAPI-Desktop-Debug/ -lDLLRestAPI

INCLUDEPATH += $$PWD/../DLLRestAPI
DEPENDPATH += $$PWD/../DLLRestAPI

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLSerialport-Desktop-Debug/release/ -lDLLSerialport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLSerialport-Desktop-Debug/debug/ -lDLLSerialport
else:unix:!macx: LIBS += -L$$PWD/../build-DLLSerialport-Desktop-Debug/ -lDLLSerialport

INCLUDEPATH += $$PWD/../DLLSerialport
DEPENDPATH += $$PWD/../DLLSerialport
