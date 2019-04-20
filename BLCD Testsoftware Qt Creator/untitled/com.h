#ifndef COM_H
#define COM_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QString>


class Com : public QObject {
    Q_OBJECT
    QSerialPort* portCom=NULL;


public:
    Com();
    ~Com();
    int Baud;
    QString Port;
    int portOpened = 0;

public slots:
    void process();
    void initPort();
    void setBaud(int setBaud);
    void setPort(QString setPort);
    void writeData (QByteArray data);
signals:
    void finished();
    void error(QString err);
    void openPortOk(bool stat);
    void received (QByteArray readData);
private:
    // add your variables here
};

#endif // COM_H
