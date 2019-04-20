#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QMap>
#include "json.h"

class Config : public QObject
{
    Q_OBJECT

public:

    JSON json;
    QMap<QString, QString> config_map;

    Config();


public slots:
    void ini();
    void Map_To_JsonFile();
    void JsonFile_To_Map();


signals:
    void sigBaud(int sigBaud);
    void sigPort(QString sigPort);
};

#endif // CONFIG_H
