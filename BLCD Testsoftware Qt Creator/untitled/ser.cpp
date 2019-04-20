#include "ser.h"

#include <QDebug>
#include <QQueue>
#include <QString>

#define STX 0x65
#define ETX 0x0D

Ser::Ser()
{
  state = PROOF_STX;
}

void Ser::Rec_Input(QByteArray input)
{
    for (int i = 0; i < input.count(); i++)
    {
        switch (state)
        {
            case PROOF_STX:
            {
                if (input[i] == STX) state = STORE_DLC;
                break;
            }

            case STORE_DLC:
            {
                ProtLen = input[i];
                RecBufCnt = 0;
                state = STORE_DATA;
                RecBuf.clear();
                break;
            }

            case STORE_DATA:
            {
                if (RecBufCnt < ProtLen)
                {
                    RecBuf.append(input[i]);
                    RecBufCnt++;
                }

                if (RecBufCnt == ProtLen) state = PROOF_CHK;

                break;
            }

            case PROOF_CHK:
            {
                int Chk = 0;

                Chk ^= STX;
                Chk ^= ProtLen;

                for (int j = 0; j < ProtLen; j++) Chk ^=  RecBuf[j];

                if (input[i] == Chk) state = PROOF_ETX;
                else state = PROOF_STX;

                break;
            }

            case PROOF_ETX:
            {
                if (input[i] == ETX)
                {
                    state = PROOF_STX;
                    emit Rec_Output(RecBuf);
                }
                else state = PROOF_STX;

                break;
            }

            default: break;
        }
    }
}

void Ser::Snd_Input(QByteArray input)
{
    SndBuf.clear();
    int Cnt = 0;
    SndBuf[Cnt++] = STX;
    SndBuf[Cnt++] = input.count();
    for (int i = 0; i < input.count(); i++) SndBuf[Cnt++] = input[i];

    int Chk = 0;
    Chk ^= STX;
    Chk ^= input.count();
    for (int i = 0; i < input.count(); i++) Chk ^=  input[i];

    SndBuf[Cnt++] = Chk;
    SndBuf[Cnt++] = ETX;

    emit Snd_Output(SndBuf);
}

void Ser::Debug_HEX(QByteArray input)
{
    QByteArray qbyte;
    QDebug deb = qDebug();

    deb << "Length" << input.count();
    deb << "HEX";

    for (int i = 0; i < input.count(); i++)
    {
        qbyte.clear();
        qbyte.append(input[i]);
        deb << qbyte.toHex();
    }
}

void Ser::Debug_ASCII(QByteArray input)
{
    QDebug deb = qDebug();

    deb << "Length" << input.count();
    deb << "ASCII";
    deb << input.simplified();
}
