QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += DLL_LOGGEDIN_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dll_loggedin.cpp \
    loggedwindow.cpp

HEADERS += \
    DLL_loggedin_global.h \
    dll_loggedin.h \
    loggedwindow.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    loggedwindow.ui
