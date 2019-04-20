#ifndef SER_H
#define SER_H

#include <QObject>
#include <QString>
#include <QByteArray>


class Ser: public QObject {

    Q_OBJECT

    enum tyen_state
    {
      PROOF_STX,
      STORE_DLC,
      STORE_DATA,
      PROOF_CHK,
      PROOF_ETX
    };

    // Receive
    enum tyen_state state = PROOF_STX;
    int ProtLen;
    int RecBufCnt;
    QByteArray RecBuf;

    // Transmit
    QByteArray SndBuf;


public:
    Ser();

public slots:
    void Rec_Input(QByteArray input);
    void Snd_Input(QByteArray input);
    void Debug_HEX (QByteArray input);
    void Debug_ASCII (QByteArray input);
signals:
    void Rec_Output(QByteArray output);
    void Snd_Output(QByteArray output);
};

#endif // SER_H
