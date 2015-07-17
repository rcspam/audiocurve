QT += core
QT -= gui
TARGET = AudioCurve
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += audiocurve.cpp sox.cpp
HEADERS += sox.h
QMAKE_CLEAN += Makefile target
OTHER_FILES += README.md LICENSE
DESTDIR = build
OBJECTS_DIR = $$DESTDIR/tmp
MOC_DIR = $$DESTDIR/tmp
RCC_DIR = $$DESTDIR/tmp
unix {
    isEmpty(PREFIX) {
        PREFIX = ~/.local/share/INRIA/Natron/Plugins
    }
    target.path = $${PREFIX}
    target_icon.path = $${PREFIX}
    target_icon.files = AudioCurve.png
    target_py.path = $${PREFIX}
    target_py.files = AudioCurve.py
    INSTALLS += target target_icon target_py
}
