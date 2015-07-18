# AudioCurve
#
# Copyright (c) 2015, Ole-André Rodlie <olear@fxarena.net>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
