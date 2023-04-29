QT -= gui
QT += widgets
QT += network
QT += multimedia

TEMPLATE = lib
DEFINES += DLL_WITHDRAW_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    withdraw.cpp

HEADERS += \
    DLL_withdraw_global.h \
    withdraw.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    withdraw.ui
