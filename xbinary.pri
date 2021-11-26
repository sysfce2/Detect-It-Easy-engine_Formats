greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/subdevice.h \
    $$PWD/xbinary.h \
    $$PWD/xbinary_def.h

SOURCES += \
    $$PWD/subdevice.cpp \
    $$PWD/xbinary.cpp

DISTFILES += \
    $$PWD/xbinary.cmake
