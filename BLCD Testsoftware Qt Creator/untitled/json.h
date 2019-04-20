#ifndef JSON_H
#define JSON_H

#include <QJsonDocument>
#include <QFile>


class JSON
{
public:
    JSON();
    QJsonDocument load(QString fileName);
    void save(QJsonDocument document, QString fileName);
};

#endif // JSON_H
