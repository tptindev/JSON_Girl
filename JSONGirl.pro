QT -= gui

TEMPLATE = lib
DEFINES += JSONGIRL_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JSONGirl.cpp

HEADERS += \
    JSONGirl_global.h \
    JSONGirl.h

# Default rules for deployment.
win32 {
    headers.path = $${PWD}/$${TARGET}/include
    headers.files += $${HEADERS}
    INSTALLS += headers
    message("path: " $${PWD}/project/)
}
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
