QT += gui
QT += widgets
QT += network
QT += multimedia

TEMPLATE = lib
DEFINES += CHOOSEACTION_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooseaction.cpp \
    enviroment.cpp \
    transactions.cpp

HEADERS += \
    chooseAction_global.h \
    chooseaction.h \
    enviroment.h \
    transactions.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    chooseaction.ui \
    transactions.ui
