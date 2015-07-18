#ifndef SOX_H
#define SOX_H

#include <QObject>

class Sox : public QObject
{
    Q_OBJECT
public:
    explicit Sox(QObject *parent = 0);

signals:
    void error(QString msg);
    void status(QString msg);

public slots:
    QString bin();
    QString about();
    QString dat(QString filename, float fps, int duration, bool x, bool y, int xFactor, int yFactor);
    QString formats();
    float duration(QString filename, float fps);
};

#endif // SOX_H
