#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <sox.h>
#include <QFile>
#include <QDir>

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
    int fps = 0;
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
        if (args.at(i)=="-fps")
            foundFps = true;
        if (foundFps && args.at(i)!="-fps") {
            if (!args.at(i).isEmpty())
                fps = args.at(i).toInt();
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
    }
    if (!filename.isEmpty() && (curveX||curveY) && fps>0 && frames>0 && (heightX>0||heightY>0)) {
        QString data = audio.dat(filename,fps,frames,curveX,curveY,heightX,heightY);
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
            }
            else {
                qDebug() << data;
            }
        }
    }
    else {
        qDebug() << "Usage: -input audiofile -output textfile -x -y -fps 24 -frames 240 -cX 100 -cY 100";
        return 1;
    }
    
    return 0;
}
