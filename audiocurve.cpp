/*
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
*/

#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDir>
#include "sox.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("AudioCurve");
    Sox audio;
    if (audio.bin().isEmpty()) {
        qDebug() << "Unable to find SoX, please install SoX.";
        return 1;
    }
    QStringList args = QCoreApplication::arguments();
    QString filename;
    QString tmpfile;
    bool curveX = false;
    bool curveY = false;
    bool forceNull = false;
    float fps = 0;
    int frames = 0;
    int heightX = 0;
    int heightY = 0;
    bool foundInput = false;
    bool foundOutput = false;
    bool foundFps = false;
    bool foundFrames = false;
    bool foundHeightX = false;
    bool foundHeightY = false;
    for (int i = 1; i < args.size(); ++i) {
        if (args.at(i)=="-input")
            foundInput = true;
        if (foundInput && args.at(i)!="-input") {
            if (!args.at(i).isEmpty())
                filename= args.at(i);
            foundInput = false;
        }
        if (args.at(i)=="-output")
            foundOutput = true;
        if (foundOutput && args.at(i)!="-output") {
            if (!args.at(i).isEmpty())
                tmpfile= args.at(i);
            foundOutput = false;
        }
        if (args.at(i)=="-x")
            curveX = true;
        if (args.at(i)=="-y")
            curveY = true;
        if (args.at(i)=="-xy") {
            curveX = true;
            curveY = true;
        }
        if (args.at(i)=="-fps")
            foundFps = true;
        if (foundFps && args.at(i)!="-fps") {
            if (!args.at(i).isEmpty())
                fps = args.at(i).toFloat();
            foundFps = false;
        }
        if (args.at(i)=="-frames")
            foundFrames = true;
        if (foundFrames && args.at(i)!="-frames") {
            if (!args.at(i).isEmpty())
                frames = args.at(i).toInt();
            foundFrames = false;
        }
        if (args.at(i)=="-cX")
            foundHeightX = true;
        if (foundHeightX && args.at(i)!="-cX") {
            if (!args.at(i).isEmpty())
                heightX = args.at(i).toInt();
            foundHeightX = false;
        }
        if (args.at(i)=="-cY")
            foundHeightY = true;
        if (foundHeightY && args.at(i)!="-cY") {
            if (!args.at(i).isEmpty())
                heightY = args.at(i).toInt();
            foundHeightY = false;
        }
        if (args.at(i)=="-alwaysXY")
            forceNull = true;
    }
    if (!filename.isEmpty() && (curveX||curveY) && fps>0 && frames>0 && (heightX>0||heightY>0)) {
        QString data = audio.dat(QDir::toNativeSeparators(filename),fps,frames,curveX,curveY,heightX,heightY,forceNull);
        if (data.isEmpty()) {
            qDebug() << "Unable to generate curve data";
            return 1;
        }
        else {
            if (!tmpfile.isEmpty()) {
                QFile output(QDir::toNativeSeparators(tmpfile));
                if (output.exists())
                    output.remove();
                if (output.open(QIODevice::WriteOnly|QIODevice::Text)) {
                    QTextStream stream(&output);
                    stream << data;
                    output.close();
                }
                else {
                    qDebug() << output.errorString();
                    return 1;
                }
            }
            else {
                qDebug() << data;
            }
        }
    }
    else {
        qDebug() << "AudioCurve usage example: -input audiofile (-output textfile) -x (-y|-xy) -fps 24 -frames 240 -cX 100 -cY 100 (-alwaysXY)";
        return 1;
    }
    
    return 0;
}
