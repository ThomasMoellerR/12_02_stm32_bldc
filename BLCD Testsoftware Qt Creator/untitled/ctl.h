#ifndef CTL_H
#define CTL_H

#include <QObject>
#include <QTableWidgetItem>
#include <QByteArray>
#include <QTimer>
#include <QQueue>

class Ctl : public QObject
{
    Q_OBJECT

    QQueue <QByteArray> queue;

public:
    Ctl();


public slots:
    void process();
    void message_in (QByteArray data);
    void timer (void);

signals:
    void finished();
    void message_out(QByteArray data);

};

#endif // CTL_H
