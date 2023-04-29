QT       += core gui
QT += serialport
QT +=network
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enviroment.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    enviroment.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/chooseAction/build/release/ -lchooseAction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/chooseAction/build/debug/ -lchooseAction
else:unix: LIBS += -L$$PWD/chooseAction/build/ -lchooseAction

INCLUDEPATH += $$PWD/chooseAction
DEPENDPATH += $$PWD/chooseAction

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLL_endscene/build/release/ -lDLL_endscene
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLL_endscene/build/debug/ -lDLL_endscene
else:unix: LIBS += -L$$PWD/DLL_endscene/build/ -lDLL_endscene

INCLUDEPATH += $$PWD/DLL_endscene
DEPENDPATH += $$PWD/DLL_endscene

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLL_loggedin/build/release/ -lDLL_loggedin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLL_loggedin/build/debug/ -lDLL_loggedin
else:unix: LIBS += -L$$PWD/DLL_loggedin/build/ -lDLL_loggedin

INCLUDEPATH += $$PWD/DLL_loggedin
DEPENDPATH += $$PWD/DLL_loggedin

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLL_withdraw/build/release/ -lDLL_withdraw
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLL_withdraw/build/debug/ -lDLL_withdraw
else:unix: LIBS += -L$$PWD/DLL_withdraw/build/ -lDLL_withdraw

INCLUDEPATH += $$PWD/DLL_withdraw
DEPENDPATH += $$PWD/DLL_withdraw
