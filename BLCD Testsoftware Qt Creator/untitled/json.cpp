#include "json.h"


JSON::JSON()
{

}

QJsonDocument JSON::load(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
    jsonFile.close();
}

void JSON::save(QJsonDocument document, QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
    jsonFile.close();
}
